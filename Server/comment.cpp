#include "comment.h"


Comment::Comment(const QString &commentValue, Comment *commectReply) : commentValue(commentValue),
    commectReply(commectReply)
{}


void Comment::setcommectValue(const QString &newComment)
{
    commentValue = newComment;
}

QString Comment::getcommectValue() const
{
    return commentValue;
}

Comment* Comment::getcommectReply() const
{
    return commectReply;
}

void Comment::setcommectReply(Comment *newCommectReply)
{
    this->commectReply = newCommectReply;
}
