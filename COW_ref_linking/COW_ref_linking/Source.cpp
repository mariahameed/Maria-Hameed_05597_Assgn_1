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
	SP *next;
	SP *prev;

public:
	SP()
	{
		pData = 0;
		this->next = nullptr;
		this->prev = nullptr;
	}

	SP(StringBuffer* pValue)
	{
		pData = pValue;
		this->next = nullptr;
		this->prev = nullptr;
		cout << endl << "HERE cons" << endl;
		//		cout << endl << pData->_refcount << "references remaining" << endl;
	}

	void append(char c)
	{
		char *temp = new char[pData->get_length()];
		temp = pData->get_string();

		SP * sp = this->prev;
		sp->next = this->next;
		this->next->prev = this->prev;

		//		pData->_refcount--;
		pData = new StringBuffer(temp, pData->get_length());

		pData->append(c);
		//		pData->_refcount = 0;
		//pData->_refcount++;
		this->next = NULL;
		this->prev = NULL;
	}

	SP(SP& sp)
	{
		pData = sp.pData;											//Copy the data and reference pointer and increment the reference count
		if (sp.next == NULL)
		{
			sp.next = this;
			sp.prev = this;
			this->next = &sp;
			this->prev = &sp;
		}
		else
		{
			SP *temp = sp.next;
			sp.next = this;
			this->next = temp;
			temp->prev = this;
			this->prev = &sp;

		}

		cout << endl << "HERE ++" << endl;
	}

	~SP()
	{
		//if (this->next == this->prev &&  this->prev  == this)// Decrement the reference count. If reference become zero delete the data

		SP * sp = this->prev;
		sp->next = this->next;
		this->next->prev = this->prev;

		this->next = NULL;
		this->prev = NULL;

		//if (pData->_refcount-- == 0)// Decrement the reference count. If reference become zero delete the data
		if (this->next == this->prev &&  this->prev == this)
		{
			delete pData;
		}
		cout << endl << "HERE --" << endl;
	}

	StringBuffer& operator* ()
	{
		return *pData;
	}

	StringBuffer* operator-> ()
	{
		return pData;
	}

/*	SP& operator = (const SP& sp)
	{
		return *this;
	}
	*/
};


void main()
{
	SP p(new StringBuffer("first pointer", 4));

	p->print_String();
	{
		SP q = p;
		q->print_String();

		p.append('a');

		SP r = p;
		p->print_String();
	}
	p->print_String();

	getchar();
}