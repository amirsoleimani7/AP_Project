#include "comment.h"

int Comment::commentIdGenerator = 1;
Comment::Comment(const QString &commentValue, Comment *commentReply) : commentValue(commentValue),
    commentReply(commentReply), commentId(commentIdGenerator+lastCommentId)
{
    commentIdGenerator ++;
}

Comment::Comment(const Comment &other)
{
    commentId = other.commentId;
    commentValue = other.commentValue;
    commentReply = other.commentReply;
}


void Comment::setcommectValue(const QString &newComment)
{
    commentValue = newComment;
}

QString Comment::getcommectValue() const
{
    return commentValue;
}

Comment* Comment::getcommentReply() const
{
    return commentReply;
}

void Comment::setcommentReply(Comment *newCommentReply)
{
    this->commentReply = newCommentReply;
}

bool Comment::operator ==(const Comment &other)
{
    return (commentId == commentId);
}
