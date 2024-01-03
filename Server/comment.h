#ifndef COMMENT_H
#define COMMENT_H
#include <QString>
#include <QVector>

class Comment
{
private:
    QString commentValue;
    // int commentId;

    Comment *commectReply;
public:
    Comment(const QString &commentValue, Comment *commectReply);
    void setcommectValue(const QString &newComment);
    QString getcommectValue() const;
    Comment* getcommectReply() const;
    void setcommectReply(Comment *newCommectReply);
};

#endif // COMMENT_H
