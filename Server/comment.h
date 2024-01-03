#ifndef COMMENT_H
#define COMMENT_H
#include <QString>
#include <QVector>
#include "task.h"

class Comment
{
private:
    static int commentIdGenerator;
    int commentId;
    int lastCommentId;
    QString commentValue;
    Task commentTask;
    int commentReplyId;
public:
    Comment(const QString &commentValue, int commentReplyId ,Task newCommentTask);
    Comment(const Comment& other);
    QString getcommectValue() const;
    int getcommentReply() const;
    int getCommentId() const;
    int getLastCommentId() const;
    void setcommectValue(const QString &newComment);
    void setcommentReply(int newCommentReply);
    bool operator ==(const Comment& other);
    void setLastCommentId(int newLastCommentId);
};

#endif // COMMENT_H
