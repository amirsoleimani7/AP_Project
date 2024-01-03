#include "comment.h"

int Comment::commentIdGenerator = 1;
int Comment::getCommentId() const
{
    return commentId;
}

int Comment::getLastCommentId() const
{
    return lastCommentId;
}

void Comment::setLastCommentId(int newLastCommentId)
{
    lastCommentId = newLastCommentId;
}

Comment::Comment(const QString &commentValue, int commentReplyId,Task newCommentTask) : commentValue(commentValue),
    commentReplyId(commentReplyId),commentTask(newCommentTask) , commentId(commentIdGenerator+lastCommentId)
{
    commentIdGenerator ++;
}

Comment::Comment(const Comment &other)
{
    commentId = other.commentId;
    commentValue = other.commentValue;
    commentReplyId = other.commentReplyId;
    commentTask = other.commentTask;
}


void Comment::setcommectValue(const QString &newComment)
{
    commentValue = newComment;
}

QString Comment::getcommectValue() const
{
    return commentValue;
}

int Comment::getcommentReply() const
{
    return commentReplyId;
}

void Comment::setcommentReply(int newCommentReply)
{
    this->commentReplyId = newCommentReply;
}

bool Comment::operator ==(const Comment &other)
{
    return (commentId == commentId);
}
