#include <stdio.h>
#include <string.h>
#include <iostream>
using namespace std;

void rc4_init(unsigned char*s, unsigned char*key, unsigned long Len)
{
	int i = 0, j = 0;
	char k[256] = { 0 };
	unsigned char tmp = 0;
	for (i = 0; i < 256; i++)
	{
		s[i] = i;
		k[i] = key[i%Len];
	}

	//Swap s[i] and s[j]
	for (i = 0; i < 256; i++)
	{
		j = (j + s[i] + k[i]) % 256;
		tmp = s[i];
		s[i] = s[j];
		s[j] = tmp;
	}
}

void rc4_crypt(unsigned char*s, unsigned char*Data, unsigned long Len)
{
	int i = 0, j = 0, t = 0;
	unsigned long k = 0;
	unsigned char tmp;
	for (k = 0; k < Len; k++)
	{
		i = (i + 1) % 256;
		j = (j + s[i]) % 256;
		tmp = s[i];
		s[i] = s[j];																								//Swap s[x] and s[y]
		s[j] = tmp;
		t = (s[i] + s[j]) % 256;
		Data[k] ^= s[t];
	}
}

int main()
{
	cout << "Student number: 57117212\tStudent name: Ðí³¯Ñô\n\n";				//Identification

	unsigned char s[256] = { 0 }, s2[256] = { 0 };												//Sbox
	char key[256] = { "abcde" };																		//Key
	char data[512] = "Southeast University";														//Plaintext
	unsigned long len = strlen(data);																//Get the length of plaintext
	int i = 0;

	cout << "Text = " << data << "\tLength of plaintext = " << len << endl;
	printf("Key = %s \t\t\tLength of key= %d\n\n", key, strlen(key));
	rc4_init(s, (unsigned char*)key, strlen(key));												//Initialization of key
	printf("S has been initialized successfully.\n\n");

	cout << "S-box has been set as following: \n";
	for (i = 0; i < 256; i++)
	{
		printf("%02X", s[i]);																				//Output the S-box in hexadecimal
		if (i && (i + 1) % 32 == 0) cout<<endl;
	}
	cout << endl;

	for (i = 0; i < 256; i++)																				//Save s in s2 temporarily
	{
		s2[i] = s[i];
	}
	
	//Encrypt
	printf("The ciphertext:\n");
	rc4_crypt(s, (unsigned char*)data, len);
	cout << "Text = " << data << endl;
	
	//Decrypt
	printf("The plaintext:\n");
	rc4_crypt(s2, (unsigned char*)data, len);
	cout << "Text = " << data << endl << endl;

	system ("pause");
	return 0;
}