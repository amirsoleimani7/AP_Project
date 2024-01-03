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
    QString getcommectValue() const;
    Comment* getcommentReply() const;
    int getCommentId() const;
    int getLastCommentId() const;
    void setcommectValue(const QString &newComment);
    void setcommentReply(Comment *newCommentReply);
    bool operator ==(const Comment& other);
    void setLastCommentId(int newLastCommentId);
};

#endif // COMMENT_H
