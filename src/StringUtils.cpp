#include "StringUtils.h"

namespace StringUtils{

std::string Slice(const std::string &str, ssize_t start, ssize_t end) noexcept{
    std::string Temp = str;
    int tmpStart = start;
    int tmpEnd = end;
    size_t Length = Temp.length();

    if (tmpStart < 0){ // return empty string if negative start passed
        return "";
    }
    if (tmpEnd < 0){ // turn end positive if negative
        tmpEnd = Length + tmpEnd;
    }

    return Temp.substr(tmpStart, tmpEnd - tmpStart);
}

std::string Capitalize(const std::string &str) noexcept{
    std::string Temp = str;

    if(!Temp.empty()){
        Temp[0] = toupper(Temp[0]); // uppercase first letter
        for(size_t i = 1; i < Temp.length(); i++){
            Temp[i] = tolower(Temp[i]); // lowercase all other letters
        }
    }
    return Temp;
}

std::string Upper(const std::string &str) noexcept{
    std::string Temp = str;

    if(!Temp.empty()){
        for(size_t i = 0; i < Temp.length(); i++){
            Temp[i] = toupper(Temp[i]); // uppercase all letters
        }
    }

    return Temp;
}

std::string Lower(const std::string &str) noexcept{
    std::string Temp = str;

    if(!Temp.empty()){
        for(size_t i = 0; i < Temp.length(); i++){
            Temp[i] = tolower(Temp[i]); // lowercase all letters
        }
    }

    return Temp;
}

std::string LStrip(const std::string &str) noexcept{
    std::string Temp = str;
    size_t i = 0;
    size_t Length = Temp.length();

    // find first nonspace character
    while(i < Length && isspace(Temp[i])){
        i++;
    }

    // return everything but left space characters
    return Temp.substr(i);
}

std::string RStrip(const std::string &str) noexcept{
    std::string Temp = str;
    int Length = Temp.length();
    int i = Length - 1;

    // find first nonspace characters from end
    while(i >= 0 && isspace(Temp[i])){
        i--;
    }

    // return everything but right space characters
    return Temp.substr(0, i+1);
}

std::string Strip(const std::string &str) noexcept{
    std::string Temp = str;
    return LStrip(RStrip(Temp)); // strip left then strip right
}

std::string Center(const std::string &str, int width, char fill) noexcept{
    
    int Length = str.length();
    int LeftWidth = (width - Length) / 2; // find desired left spacing

    // right then left justify
    return LJust(RJust(str, Length + LeftWidth, fill), width, fill); 
}

std::string LJust(const std::string &str, int width, char fill) noexcept{

    std::string Temp = str;
    int Length = Temp.length();

    if (width <= Length){ // return string if width < its actual length
        return Temp;
    }

    for (int i = Length + 1; i <= width; i++){ // add fill chars to right
        Temp += fill;
    }

    return Temp;
}

std::string RJust(const std::string &str, int width, char fill) noexcept{
    std::string Result = "";
    std::string Temp = str;
    int Length = Temp.length();
    int LeftWidth = width - Length;


    if (width < Length){ // return string if width is < its actual length
        return Temp;
    }

    for (int i = 0; i < LeftWidth; i++){ // add fill chars to empty string
        Result += fill;
    }

    Result += Temp; // add string to fill chars


    return Result;
}

std::string Replace(const std::string &str, const std::string &old, const std::string &rep) noexcept{
    std::string Result = "";
    int Length = str.length();
    int OldLength = old.length();

    int i = 0;

    
    while(i < Length){
        // if old found, add replacement
        if (str.substr(i, OldLength) == old){
            Result += rep;
            i += OldLength;
        }

        // otherwise add the next letter of the original string
        else{
            Result += str[i];
            i++;
        }
        
    }

    return Result;
}

std::vector< std::string > Split(const std::string &str, const std::string &splt) noexcept{
    std::vector<std::string> Result;
    std::string Temp = str;
    std::string SubTemp;
    
    int Length = Temp.length();
    int SpltLength = splt.length();
    int Start = 0;
    int i = 0;

    // when splt is "" split at whitespace 
    if(splt == ""){
        while(i <= Length){
            // find whitespaces
            if (isspace(Temp[i])){

                // add characters between whitespaces/ends to vector
                Result.push_back(Temp.substr(Start, i-Start)); 
                i++;
                Start = i;

            }
            else{
                i++; 
            }
        }
        
    }

    // when splt is non-whitespace
    else{
        while(i < Length-SpltLength){
            // find instances of splt
            if ((Temp.substr(i, SpltLength) == splt)){

                // add characters between splts/ends to vector
                Result.push_back(Temp.substr(Start, i-Start));
                i += SpltLength;
                Start = i;
            }
            else{
                i++;
            }
        }
    }

    // add last split to vector
    Result.push_back(Temp.substr(Start, Length-Start));

    return Result;
}

std::string Join(const std::string &str, const std::vector< std::string > &vect) noexcept{
    int inputSize = vect.size();
    std::string Result = "";

    // add each word in vector to empty string with separator after
    for (int i = 0; i < inputSize - 1; i++){
        Result += vect[i];
        Result += str;
    }

    // add last word without separator
    Result += vect[inputSize-1];

    return Result;
}

std::string ExpandTabs(const std::string &str, int tabsize) noexcept{
    std::string Result = "";
    int Length = str.length();
    int i = 0;
    int TabIndex;

    while (i < Length){

        // find tabs
        if (str[i] == '\t'){

            // find how many spaces needed until next tab stop
            TabIndex = (i + 1) % tabsize;

            // add spaces
            if (TabIndex!= 0){
                for (int j = 0; j <= (tabsize - TabIndex); j++){
                    Result += " ";
                }

            }
            else{
                for (int k = 0; k < tabsize; k++){
                    Result += " ";
                }
            }
        }

        // add next character in string
        else{
            Result += str[i];
        }

        i++;
    }

    return Result;
}

int EditDistance(const std::string &left, const std::string &right, bool ignorecase) noexcept{
    std::string tmpLeft;
    std::string tmpRight;

    int Min;
    int Lev1;
    int Lev2;
    int Lev3;

    // lowercase both string parameters
    if (ignorecase){
        tmpLeft = Lower(left);
        tmpRight = Lower(right);
    }
    else{
        tmpLeft = left; // a
        tmpRight = right; // b
    }

    // base case 1
    if (tmpLeft.length() == 0){
        return tmpRight.length();
    }

    // base case 2
    else if(tmpRight.length() == 0){
        return tmpLeft.length();
    }

    // find levenshtein distance of tail(a) and tail(b) if first letter of a and b 
    // is the same
    else if(tmpLeft[0] == tmpRight[0]){
        return EditDistance(tmpLeft.substr(1, tmpLeft.length() - 1), tmpRight.substr(1, tmpRight.length() - 1));
    }

    else {
        // find the minimum levenshtein distance of tail(a) and b,
        // a and tail(b)), tail(a) and tail(b))
        Lev1 = EditDistance(tmpLeft.substr(1, tmpLeft.length() - 1), tmpRight);
        Lev2 = EditDistance(tmpLeft, tmpRight.substr(1, tmpRight.length() - 1));
        Lev3 = EditDistance(tmpLeft.substr(1, tmpLeft.length() - 1), tmpRight.substr(1, tmpRight.length() - 1));

        Min = Lev1;

        if (Lev2 < Min){
            Min = Lev2;
        }

        else if (Lev3 < Min){
            Min = Lev3;
        }

        // add 1 to the minimum
        return 1 + Min;
    }

    return 0;
}

};