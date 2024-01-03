#ifndef COMMENT_H
#define COMMENT_H
#include <QString>
#include <QVector>

class Comment
{
private:
    static int commentIdGenerator;
    int commentId;
    int lastCommentId;
    QString commentValue;
    Comment *commentReply;
public:
    Comment(const QString &commentValue, Comment *commentReply);
    Comment(const Comment& other);
    void setcommectValue(const QString &newComment);
    QString getcommectValue() const;
    Comment* getcommentReply() const;
    void setcommentReply(Comment *newCommentReply);
    bool operator ==(const Comment& other);
};

#endif // COMMENT_H
