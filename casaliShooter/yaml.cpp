/**
* @file yaml.cpp
* @brief YAML : Allows to parse the configurable file
* @author Gonzales, Djerian, Leydier, Volpei, Dugourd
* @version 1.0
* @date 11/01/2022
*/
#include <vector>

#include "fstream"

#include "yaml.h"

using namespace std;

/** @brief Generator of a vector with ASCII references
*
*@param[in] fileName : Name of the file
*@returns vector<unsigned> with ASCII references
*
*/
vector<unsigned> vecParam (const string & fileName) {
    const vector<string> vecValuesUns = {"KBack", "KConfirm","KLeftMenu", "KRightMenu", "KMovingDownMenu","KMovingUpMenu", "KMovingLeftGame", "KMovingRightGame", "KShootGame", "KWidthMissile", "KLenghtMissile", "KWidthTorpedoPPs", "KLenghtTorpedoPPs", "KWidthTorpedoUFO", "KLenghtTorpedoUFO"};
    ifstream ifs(fileName);
    char valChar;
    unsigned valUnsigned;
    vector<unsigned> vecValues;
    for (string key; ifs >> key;) {
        ifs >> valChar;
        if (vecValuesUns.end() != find(vecValuesUns.begin(), vecValuesUns.end(), key)) {
            ifs >> valUnsigned;
            vecValues.push_back(valUnsigned);
        }
    }
    return vecValues;

}
