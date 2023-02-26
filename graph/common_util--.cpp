// #include "common_util.h"

// // s:待分割的字符串
// // v:分割后的字符串
// // c：分隔符
// void SplitString(const std::string& source_str, std::vector<std::string>& destination_strs, const std::string& sp)
// {
//   std::string::size_type pos1, pos2;
//   pos2 = source_str.find(sp);
//   pos1 = 0;
//   while(std::string::npos != pos2)
//   {
//     destination_strs.push_back(source_str.substr(pos1, pos2 - pos1));
//     pos1 = pos2 + sp.size();
//     pos2 = source_str.find(sp, pos1);
//   }
//   //如果源文件的最后一个字符是分隔符，pos1的大小就等于字符串的长度
//   if(pos1 != source_str.length())
//     destination_strs.push_back(source_str.substr(pos1));
// }