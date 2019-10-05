#pragma once
#include "tinyxml.h"

const unsigned int NUM_INDENTS_PER_SPACE = 2;

const char* getIndent(unsigned int);
const char* getIndentAlt(unsigned int);
int dump_attribs_to_stdout(TiXmlElement*, unsigned int);
void dump_to_stdout(TiXmlNode*, unsigned int);
void dump_to_stdout(const char*);