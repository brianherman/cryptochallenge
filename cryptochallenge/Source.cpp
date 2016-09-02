#include <string>
#include <iostream>
char* CODES = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/=";
std::string base64_encode(char* in, int length) 
{

		std::string out;
		int b;
		for (int i = 0; i < length; i += 3) {
				b = (in[i] & 0xFC) >> 2;
				out += CODES[b];
				b = (in[i] & 0x03) << 4;
				if (i + 1 < length) {
						b |= (in[i + 1] & 0xF0) >> 4;
						out += CODES[b];
						b = (in[i + 1] & 0x0F) << 2;
						if (i + 2 < length) {
								b |= (in[i + 2] & 0xC0) >> 6;
								out += CODES[b];
								b = (in[i + 2] & 0x3F);
								out += CODES[b];
						}
						else {
								out += CODES[b];
								out += "=";
						}
				}else {
						out += CODES[b];
						out += "==";
				}
		}
		return out;
}
int main() {
		char* s = "Man is distinguished, not only by his reason, but by this singular passion from\nother animals, which is a lust of the mind, that by a perseverance of delight\nin the continued and indefatigable generation of knowledge, exceeds the short\nvehemence of any carnal pleasure.";
		std::cout << base64_encode(s, strlen(s));
		
}