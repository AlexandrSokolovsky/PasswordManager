
class PasswordGenerator
{
private: 	
		
	string pass_name;
	int length;	
	

	struct keys     //Keys for making password
	{
		bool numbers,
			low_letter,
			cap_letter;
	}settings;


public:
	struct all_data
	{		
		string pass_name;		//password's name
		int length;			//password's length
		bool real=0;		//to know encrypted or decrypted password is
		string depass;	//decrypted password	
		string epass;    //encrypted password
		 	
					//keys
		bool numbers,			//use 0-9?     0/1
			low_letter,		//use a-z?     0/1
			cap_letter;		//use A-Z?     0/1
		
	}data;

public: 
	PasswordGenerator(int length_set=10, bool numbers_set=1, bool cap_letter_set=1, bool low_letter_set=1, string pass_name_set ="")
	{
		setDate(length_set, numbers_set, cap_letter_set, low_letter_set, pass_name_set);

	}
	


	void setDate_fromfile( bool cap_letter_set, bool low_letter_set,  bool numbers_set, string depass_set, string epass_set,int real_set, string pass_name_set, int length_set)
	{
		data.cap_letter = cap_letter_set;
		data.low_letter = low_letter_set;
		data.numbers = numbers_set;

		data.depass = depass_set;
		data.epass = epass_set;
		data.real = real_set;

		data.pass_name = pass_name_set;
		data.length = length_set;

	}


	void setDate(int length_set,bool numbers_set,bool cap_letter_set, bool low_letter_set,string pass_name_set)
	{		
		

		if (pass_name_set == "")
		{
			cout << "Input pass name" << endl;
			cin >> pass_name_set;	
			data.pass_name = pass_name_set;
		}
		else {
			pass_name = pass_name_set;
			data.pass_name = pass_name_set;
		}

		length = length_set;
		data.length = length_set;

		settings.numbers = numbers_set;
		data.numbers = numbers_set;

		settings.cap_letter = cap_letter_set;
		data.cap_letter = cap_letter_set;

		settings.low_letter = low_letter_set;		
		data.low_letter = low_letter_set;


	
		
		data.epass = CreatePassword();
	}
	
	void getDate() 
	{
		cout << "length=" << length << endl;
		cout << "settings.numbers=" << settings.numbers << endl;
		cout << "settings.low_letter=" << settings.low_letter << endl;
		cout << "settings.cap_letter=" << settings.cap_letter << endl;
	}

	all_data getAllData()
	{		
		return data;
	}
	
	void change_en_de()
	{
		swap(data.depass, data.epass);
		data.real = (data.real+1)%2 ;
	}

	string CreatePassword()
	{
		
		string num = new char[10];
		string az = new char[26];
		string AZ = new char[26];
		
		num = "0123456789";		
		az = "qwertyuiopasdfghjklzxcvbnm";
		AZ = "QWERTYUIOPASDFGHJKLZXCVBNM";
	
		string output;


		switch (settings.cap_letter + settings.low_letter + settings.numbers) {
		case 1:
		{
			if (settings.cap_letter == 1) {
				for (int i = 0; i < length; i++)
				{
					output += AZ[rand()%26];
				}
			}
			if (settings.low_letter == 1) {
				for (int i = 0; i < length; i++)
				{
					output += az[rand() % 26];
				}
			}
			if (settings.numbers == 1) {
				for (int i = 0; i < length; i++)
				{
					output += num[rand() % 10];
				}
			}
		}break;
		case 2:
		{
			if (settings.cap_letter + settings.low_letter == 2) {
				for (int i = 0; i < length; i++)
				{
					if (rand() % 2)				
						output += AZ[rand() % 26];
					else
						output += az[rand() % 26];
				}
			}
			if (settings.cap_letter + settings.numbers == 2) {
				for (int i = 0; i < length; i++)
				{
					if (rand() % 2)
						output += AZ[rand() % 26];
					else
						output += num[rand() % 10];
				}
			}
			if (settings.numbers + settings.low_letter == 2) {
				for (int i = 0; i < length; i++)
				{
					if (rand() % 2)
						output += num[rand() % 10];
					else
						output += az[rand() % 26];
				}
			}
		}break;
		case 3:
		{
			for (int i = 0; i < length; i++)
			{
				
				int r = rand() % 3;
				
				if (r == 0)
					output += num[rand() % 10];
				if(r == 1)
					output += az[rand() % 26];
				if (r == 2)
					output += AZ[rand() % 26];
			}
		}break;
		}
	
		data.depass = output;
		
		data.real = 0;	
		return Encode(output);
	}

	~PasswordGenerator()
	{

	}
	
}; 



