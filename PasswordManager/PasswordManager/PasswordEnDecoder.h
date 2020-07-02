

string Encode(string password)
{
	string encode_pass;
	
	for (int i = 0; i < password.size(); i++)
	{
		
		encode_pass.push_back(char(int(password[i]) + 3));
		
	}	
	return encode_pass;
}

string Decode(string password)
{
	string decode_pass;
	
	for (int i = 0; i < password.size(); i++)
	{
		decode_pass += char(int(password[i])-3);
	}
	
	return decode_pass;
}