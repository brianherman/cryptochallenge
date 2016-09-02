#include <string>
#include <iostream>

std::string base64_encode(std::string s) 
{

		std::string base64chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
		unsigned int c = s.length() % 3;
		std::string p = "";
		std::string r;
		if (c > 0) {
				for (; c < 3; c++) {
						p += '=';
						s += "\0";
				}
		}
		for (c = 0; c < s.length(); c += 3) {
				if (c > 0 && (c / 3 * 4) % 76 == 0) {
						r += "\r\n";
				}
				int n = (base64chars[c] << 16) + (base64chars[c+1] << 8) + (base64chars[c+2]);
				int n0 = (n >> 18) & 63;
				int n1 = (n >> 12) & 63;
				int n2 = (n >> 6) & 63;
				int n3 = n & 63;
				r += base64chars[n0] + base64chars[n1] + base64chars[n2] + base64chars[n3];
				std::cout << r;
		}
		return r.substr(0, r.length() - p.length()) + p;

}
int main() {
		std::cout << base64_encode("Man is distinguished, not only by his reason, but by this singular passion from\nother animals, which is a lust of the mind, that by a perseverance of delight\nin the continued and indefatigable generation of knowledge, exceeds the short\nvehemence of any carnal pleasure.");
}