#include<iostream>
using namespace std;



class StringBuffer{

public:
	StringBuffer();									//default constructor
	~StringBuffer();								//destructor; would delete the allocated buffer
	StringBuffer(char*, int);						//constructor to convert a char* to StringBuffer
	StringBuffer(const StringBuffer&);
	char charAt(int) const;							//returns the character at the passed index
	int length() const;                             //returns the length of the buffer
	void reserve(int);                              //allocates memory for the string, according to the passed character length
	void append(char);								//appends a single character at the end
	void print_String();							//prints the whole string
	int _refcount;									//keep track of number of references to a singel object
	char* get_string();
	int get_length()
	{
		return this->_length;
	}
private:
	char* _strbuf;                                   //buffer to store the original string
	int _length;                                     //length of the string
};


StringBuffer::StringBuffer()
{
	_strbuf = nullptr;
}

StringBuffer::StringBuffer(const StringBuffer& sb)
{
	this->_strbuf = sb._strbuf;
	this->_refcount = 0;
}

StringBuffer::StringBuffer(char* ch_arr, int size)
{
	_strbuf = new char[size];
	_length = size;
	for (int i = 0; i < size; i++)
	{
		_strbuf[i] = ch_arr[i];
	}
}

StringBuffer::~StringBuffer()
{
	for (int i = _length - 1; i >= 0; i--)
	{
		_strbuf[i] = NULL;
	}
	delete _strbuf;
	_strbuf = NULL;
}

char* StringBuffer::get_string()
{
	return this->_strbuf;
}
void StringBuffer::print_String()
{
	cout << endl << "string:" << endl;
	for (int i = 0; i < _length; i++)
	{
		cout << _strbuf[i];
		//cout << ":)";
	}
	cout << endl << _length << "chars printed" << endl;
}

void StringBuffer::append(char c)
{
	char* temp_buf = new char[_length + 1];
	temp_buf = _strbuf;
	temp_buf[_length] = c;
	_length++;
	//	delete[] _strbuf;
	//	_strbuf = NULL;
	_strbuf = new char[_length];
	_strbuf = temp_buf;
	_refcount = 1;
}



char StringBuffer::charAt(int index) const
{
	if (index > _length)
		return NULL;
	else
		return _strbuf[index];
}

void StringBuffer::reserve(int size)
{
	_strbuf = new char[size];
}


int StringBuffer::length() const
{
	return _length;
}


class SP
{
private:
	StringBuffer*    pData;       // pointer

public:
	SP()
	{
		pData = 0;
		pData->_refcount = 0;									// Increment the reference count
		pData->_refcount++;
		cout << endl << pData->_refcount << "references remaining" << endl;
	}

	SP(StringBuffer* pValue)
	{
		pData = pValue;
		pData->_refcount = 0;
		pData->_refcount++;
		cout << endl << pData->_refcount << "references remaining" << endl;
	}

	void append(char c)
	{
		char *temp = new char[pData->get_length()];
		temp = pData->get_string();

		pData->_refcount--;
		pData = new StringBuffer(temp, pData->get_length());

		pData->append(c);
		pData->_refcount = 0;
		pData->_refcount++;
	}

	SP(const SP& sp)
	{
		pData = sp.pData;											//Copy the data and reference pointer and increment the reference count
		pData->_refcount++;
	}

	~SP()
	{

		if (pData->_refcount-- == 0)// Decrement the reference count. If reference become zero delete the data
		{
			delete pData;
		}
		cout << endl << pData->_refcount << "--references remaining" << endl;
	}

	StringBuffer& operator* ()
	{
		return *pData;
	}

	StringBuffer* operator-> ()
	{
		return pData;
	}

	SP& operator = (const SP& sp)
	{
		// Assignment operator
		if (this != &sp) // Avoid self assignment
		{
			if (sp.pData->_refcount-- == 0)				//Decrement the old reference count. if reference become zero delete the old data
			{
				delete pData;
			}

			pData = sp.pData;								// Copy the data and reference pointer and increment the reference count
			sp.pData->_refcount++;
			cout << endl << sp.pData->_refcount << "++references remaining" << endl;
		}
		return *this;
	}

};


void main()
{
	SP p(new StringBuffer("first pointer", 4));

	p->print_String();
	{
		SP q = p;
		q->print_String();

		p.append('a');

		cout << "new refount for p" << p->_refcount;
		SP r = p;
		p->print_String();
	}
	p->print_String();

	getchar();
}