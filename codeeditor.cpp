#include "codeeditor.h"
#include <QtWidgets>
#include "codeeditor.h"
#include <QAbstractItemView>
#include <QCompleter>
#include <QKeyEvent>
#include <QString>
#include <QTextCursor>
#include <QTextEdit>



CodeEditor::CodeEditor(QWidget *parent) : QPlainTextEdit(parent)
{
    c=NULL;
    lineNumberArea = new LineNumberArea(this);

    connect(this, &CodeEditor::blockCountChanged, this, &CodeEditor::updateLineNumberAreaWidth);
    connect(this, &CodeEditor::updateRequest, this, &CodeEditor::updateLineNumberArea);
    connect(this, &CodeEditor::cursorPositionChanged, this, &CodeEditor::highlightCurrentLine);

    QFontMetrics metrics(this->font());
    this->setTabStopWidth(this->tabStop * metrics.width(' '));

    updateLineNumberAreaWidth(0);
    highlightCurrentLine();

    setHighlight();
}

void CodeEditor::setHighlight(){
    QFont font;
    font.setFamily("Courier");
    font.setFixedPitch(true);
    font.setPointSize(10);

    this->setFont(font);

    highlighter=new Highlighter(this->document());
}


int CodeEditor::lineNumberAreaWidth()
{
    int digits = 1;
    int max = qMax(1, blockCount());
    while (max >= 10) {
        max /= 10;
        ++digits;
    }

    int space = 3 + fontMetrics().horizontalAdvance(QLatin1Char('9')) * digits;

    return space;
}


void CodeEditor::updateLineNumberAreaWidth(int /* newBlockCount */)
{
    setViewportMargins(lineNumberAreaWidth(), 0, 0, 0);
}


void CodeEditor::updateLineNumberArea(const QRect &rect, int dy)
{
    if (dy)
        lineNumberArea->scroll(0, dy);
    else
        lineNumberArea->update(0, rect.y(), lineNumberArea->width(), rect.height());

    if (rect.contains(viewport()->rect()))
        updateLineNumberAreaWidth(0);
}


void CodeEditor::resizeEvent(QResizeEvent *e)
{
    QPlainTextEdit::resizeEvent(e);

    QRect cr = contentsRect();
    lineNumberArea->setGeometry(QRect(cr.left(), cr.top(), lineNumberAreaWidth(), cr.height()));
}


void CodeEditor::highlightCurrentLine()
{
    QList<QTextEdit::ExtraSelection> extraSelections;

    if (!isReadOnly()) {
        QTextEdit::ExtraSelection selection;

        QColor lineColor = QColor(Qt::yellow).lighter(160);

        selection.format.setBackground(lineColor);
        selection.format.setProperty(QTextFormat::FullWidthSelection, true);
        selection.cursor = textCursor();
        selection.cursor.clearSelection();
        extraSelections.append(selection);
    }

    setExtraSelections(extraSelections);
}


void CodeEditor::lineNumberAreaPaintEvent(QPaintEvent *event)
{
    QPainter painter(lineNumberArea);
    painter.fillRect(event->rect(), Qt::lightGray);


    QTextBlock block = firstVisibleBlock();
    int blockNumber = block.blockNumber();
    int top = (int) blockBoundingGeometry(block).translated(contentOffset()).top();
    int bottom = top + (int) blockBoundingRect(block).height();

    while (block.isValid() && top <= event->rect().bottom()) {
        if (block.isVisible() && bottom >= event->rect().top()) {
            QString number = QString::number(blockNumber + 1);
            painter.setPen(Qt::black);
            painter.drawText(0, top, lineNumberArea->width(), fontMetrics().height(),
                             Qt::AlignRight, number);
        }


        block = block.next();
        top = bottom;
        bottom = top + (int) blockBoundingRect(block).height();
        ++blockNumber;
    }
}


//====================================================自动补全==================================================================
QStringList getCompleteList(const QString &code, const int line, const int column)
{
    static QRegularExpression re("(<#.*#>)|\\[.*\\]");

    qInfo() << "getCompleteList:" << line << column;
    QProcess clang;
    QString tmp;
    tmp.sprintf("-code-completion-at=-:%d:%d", line, column);
    clang.start("clang", QStringList() << "-xc" << "-" <<
                "-fcolor-diagnostics" << "-fsyntax-only" << "-Xclang" << "-code-completion-macros" <<
                "-Xclang" << "-code-completion-patterns" << "-Xclang" << "-code-completion-brief-comments" <<
                "-Xclang" << tmp);
    clang.write(code.toUtf8());
    clang.closeWriteChannel();
    clang.waitForFinished();


    QStringList tip_list;

    while (!clang.atEnd()) {
        QString buf = QTextCodec::codecForLocale()->toUnicode(clang.readLine());
        QList<QString> tips = buf.split(':');
        if (tips.size() == 3) {
            //qDebug("%s", tips[2].trimmed().data());
            QString tip = tips[2].trimmed().replace(re, "");
            tip_list.append(tip);
        }
    }

    return tip_list;
}


void CodeEditor::setCompleter(QCompleter *completer)
{
    if (c) {
        QObject::disconnect(c, nullptr, this, nullptr);
    }

    c = completer;

    if (!c) {
        return;
    }

    QFont font = QFontDatabase::systemFont(QFontDatabase::FixedFont);
    font.setPointSize(10);

    c->setWidget(this);
    c->setCompletionMode(QCompleter::PopupCompletion);
    c->setCaseSensitivity(Qt::CaseInsensitive);
    c->popup()->setFont(font);
    QObject::connect(c, QOverload<const QString&>::of(&QCompleter::activated),
                     this, &CodeEditor::insertCompletion);

}

QCompleter *CodeEditor::completer() const
{
    return c;
}

void CodeEditor::insertCompletion(const QString& completion)
{
    if (c->widget() != this) {
        return;
    }

    QTextCursor tc = textCursor();
    // 判断需要额外插入的长度
    int extra = completion.length() - c->completionPrefix().length();
    tc.movePosition(QTextCursor::Left);
    tc.movePosition(QTextCursor::EndOfWord);
    tc.insertText(completion.right(extra));

    // 如果以 () <> "" 结尾的话, 将光标向左移动一位
    if (completion.endsWith("()") || completion.endsWith("<>") || completion.endsWith("\"\"")) {
        tc.movePosition(QTextCursor::Left);
        setTextCursor(tc);
    }
}

void CodeEditor::keyPressEvent(QKeyEvent *e)
{
    // 括号, 双引号自动完成
    do {
        if (e->key() == Qt::Key_QuoteDbl) {
            this->insertPlainText("\"");
        } else if (e->key() == Qt::Key_Apostrophe) {
            this->insertPlainText("'");
        } else if (e->key() == Qt::Key_BraceLeft) {
            this->insertPlainText("}");
        } else if (e->key() == Qt::Key_BracketLeft) {
            this->insertPlainText("]");
        } else if (e->key() == Qt::Key_ParenLeft) {
            this->insertPlainText(")");
        } else {
            break;
        }
        this->moveCursor(QTextCursor::Left);
    } while (0);


    if (c && c->popup()->isVisible()) {
        // 以下按键统统忽略, 注意 Backspace 并没有被忽略
        switch (e->key()) {
        case Qt::Key_Enter:
        case Qt::Key_Return:
        case Qt::Key_Escape:
        case Qt::Key_Tab:
        case Qt::Key_Backtab:
            e->ignore();
            return;
        default:
           break;
        }
    }

    bool isShortcut = ((e->modifiers() & Qt::ControlModifier) && e->key() == Qt::Key_E); // CTRL+E
    if (!c || !isShortcut) // do not process the shortcut when we have a completer
        QPlainTextEdit::keyPressEvent(e);

    const bool ctrlOrShift = e->modifiers() & (Qt::ControlModifier | Qt::ShiftModifier);
    if (!c || (ctrlOrShift && e->text().isEmpty()))
        return;

    static QString eow("~!@#$%^&*()_+{}|:\"<>?,./;'[]\\-="); // end of word
    bool hasModifier = (e->modifiers() != Qt::NoModifier) && !ctrlOrShift;
    QString completionPrefix = textUnderCursor();

    // 如果按键内容为空 || 补全前缀长度小于 3 并且不是 '.', 则不补全
    const bool isBadText = e->text().isEmpty() || (completionPrefix.length() < 3 && e->text() != "."); // || eow.contains(e->text().right(1));
    if (!isShortcut && (hasModifier || isBadText)) {
        c->popup()->hide();
        return;
    }

    // 只触发一次更新补全列表, 提高响应速度
    if (completionPrefix.length() == 3 || e->text() == ".") {
        updateCompleteList();
    }

    if (completionPrefix != c->completionPrefix()) {
        c->setCompletionPrefix(completionPrefix);
        c->popup()->setCurrentIndex(c->completionModel()->index(0, 0));
    }
    QRect cr = cursorRect();
    cr.setWidth(c->popup()->sizeHintForColumn(0)
                + c->popup()->verticalScrollBar()->sizeHint().width());

    c->complete(cr); // popup it up!
}

QString CodeEditor::textUnderCursor() const
{
    QTextCursor tc = textCursor();
    tc.select(QTextCursor::WordUnderCursor);
    return tc.selectedText();
}

void CodeEditor::focusInEvent(QFocusEvent *e)
{
    if (c) {
        c->setWidget(this);
    }
    QPlainTextEdit::focusInEvent(e);
}



void CodeEditor::updateCompleteList()
{
    // 获取光标当前位置(从 0 开始)
    const int x = textCursor().positionInBlock();
    const int y = textCursor().blockNumber();

    QStringList complete_list = getCompleteList(this->toPlainText(), y + 1, x + 1);

    c->setModel(new QStringListModel(complete_list, c));
}
