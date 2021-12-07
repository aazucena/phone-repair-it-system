#ifndef COMMENT_H
#define COMMENT_H

#include <string>


class Comment {
 public:
   Comment() {}
   Comment(int cid, std::string comment);
   ~Comment() {}

   int getCommentID ();
   std::string getDescription();
   void updateDescription(std::string newCom);

 private:
   std::string cmt;
   int commentID;
};

#endif // COMMENT_H
