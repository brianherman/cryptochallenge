#include <string>
#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <sstream>
char* CODES = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/=";
std::string base64_encode(uint8_t* in, int length) 
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
uint8_t* string_to_uint8(std::string input) {
		uint8_t* output = (uint8_t*) malloc(sizeof(input.length() * sizeof(uint8_t)));
		int count = 0;

		for_each(input.begin(), input.end(),
				[&input,&count, &output](auto x) {
				std::string temp;
				temp += input[count];
				if (temp.length() >= 2){
						std::stringstream ss;
						uint8_t target(0);
						//http://www.cplusplus.com/forum/general/101698/ read string two at a time
						//http://stackoverflow.com/questions/18346726/how-to-convert-hex-string-to-uint8/
						ss << std::hex << temp;
						if (ss >> target) {
								//std::cout << "value=" << target << '\n';
								output[count] = target;
								count++;
						}
						else {
								std::cout << "failed to read value\n";
						}
						temp = "";
				}
				}
		);
		return output;
}//cooklies
std::vector<uint8_t> fixed_xor(std::vector<uint8_t> input, std::vector<uint8_t> operand) {
		std::vector<uint8_t> output;
		for (int i=0; i<input.size(); i++)
		{
				output.push_back(input[i] ^ operand[i]);
		}
		return output;
}
int main() {
		//char* s = "Man is distinguished, not only by his reason, but by this singular passion from\nother animals, which is a lust of the mind, that by a perseverance of delight\nin the continued and indefatigable generation of knowledge, exceeds the short\nvehemence of any carnal pleasure.";
		uint8_t data[] = { 0x49, 0x27, 0x6d, 0x20, 0x6b, 0x69, 0x6c, 0x6c, 0x69, 0x6e, 0x67, 0x20, 0x79, 0x6f, 0x75, 0x72, 0x20, 0x62, 0x72, 0x61, 0x69, 0x6e, 0x20, 0x6c, 0x69, 0x6b, 0x65, 0x20, 0x61, 0x20, 0x70, 0x6f, 0x69, 0x73, 0x6f, 0x6e, 0x6f, 0x75, 0x73, 0x20, 0x6d, 0x75, 0x73, 0x68, 0x72, 0x6f, 0x6f, 0x6d};
		std::cout << string_to_uint8("49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d");
		//std::cout << base64_encode(data, 48);
		std::vector<uint8_t> xor = { 0x1c,0x01, 0x11, 0x00, 0x1f, 0x01, 0x01, 0x00, 0x06,0x1a,0x02,0x4b,0x53,0x53,0x50,0x09,0x18,0x1c };
		std::vector<uint8_t> xor2 = { 0x68,0x69,0x74,0x20,0x74,0x68,0x65,0x20,0x62,0x75,0x6c,0x6c,0x27,0x73,0x20,0x65,0x79,0x65 };
		std::vector<uint8_t> fx = fixed_xor(xor,xor2);
		std::vector<uint8_t> fa = { 0x1b,0x37,0x37,0x33,0x31,0x36,0x3f,0x78,0x15,0x1b,0x7f,0x2b,0x78,0x34,0x31,0x33,0x3d,0x78,0x39,0x78,0x28,0x37,0x2d,0x36,0x3c,0x78,0x37,0x3e,0x78,0x3a,0x39,0x3b,0x37,0x36 };
		std::string s = { "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736" };
		uint8_t* converted = string_to_uint8(s);
		for_each(fa.begin(), fa.end(), [](auto x) {
				//fixed_xor(x, 0x1);
		});
		
		for (int i = 0; i < fx.size(); ++i) {
				//std::cout << std::hex << unsigned(fx[i]);
		}
}