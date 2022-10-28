/*
    AUTHOR: Manuel Espinoza
    DATE: October 2022

    PURPOSE:
    Convert a JSON file into a C++ Unordered Map that
    maps the JSON keys to the corresponding values in
    the adecuate C++ class
*/

#pragma once
// #include <stdio.h>
// #include <iostream>
#include <fstream>
#include <assert.h>
#include <unordered_map>

namespace Jason{
    class Parser {
        private:
            static const int MAX_LENGTH = 100;
            std::unordered_map<std::string, void*> *objects; 
            std::ifstream jsonFile;

        public:
            Parser(const std::string path){
                jsonFile.open(path, std::ifstream::in);
                parseFile();
            }

            void parseFile(){
                char *line;
                assert(jsonFile.is_open());
                while (line != nullptr) {
                    jsonFile.getline(line, MAX_LENGTH);
                }
            }

            char** lexer(char *inputLine){
                char **tokens = new char*;
                int length = strlen(inputLine);
                for (int i=0; i<length; i++){
                    tokens[i] = new char;
                }
                
                /*
                Common tokens:
                    '{'
                    '}'
                    ':'
                    '['
                    ']'
                */
                int index = 0;
                int sStringIndex = 0;
                bool isString = false;
                char character;
                for (int i = 0; i < length; i++){
                    character = inputLine[i];
                    if (character == '{'
                        || character == '}'
                        || character == ':'
                        || character == '['
                        || character == ']')
                    {
                        if (isString)
                        {
                            index++;
                        }
                        tokens[index++][0] = character;
                    }
                    else{
                        tokens[index][sStringIndex++] = character;
                        isString = true;
                    }
                }
            }

            ~Parser(){
                jsonFile.close();
                delete(objects);
            }
    };
};