#include <iostream>
using namespace std;

class Holder{
	private:
		int *m_data;
		size_t m_size;
	public:
		Holder(int size){
			cout<<"Constructor por defecto"<<'\n';
			this->m_data = new int[size];
			this->m_size = size;
		}
		
		//Constructor copia
		Holder(const Holder &other){
			cout<<"Constructor de copia"<<'\n';
			this->m_data = new int[other.m_size];
			copy(other.m_data, other.m_data + other.m_size,m_data);
			this->m_size = other.m_size;
		}
		
		//Constructor de movimiento	
		Holder(Holder &&other){
			cout<<"Constructor de Movimiento"<<'\n';
			this->m_data = other.m_data;
			this->m_size = other.m_size;
			other.m_data = nullptr;
			other.m_size = 0;
		}
		
		//Operador de Asignacion Lvalue
		Holder& operator=(const Holder &other){
			cout<<"Operador de asignacion Lvalue"<<'\n';
			if(this == &other) return *this;
			delete [] m_data;
			m_data = new int[other.m_size];
			copy(other.m_data, other.m_data + other.m_size,m_data);
			m_size = other.m_size;
			return *this;
		}
		
		//Operador de Asignacion Rvalue
		Holder& operator=(Holder&& other){
			cout<<"Operador de Asignacion Rvalue"<<'\n';
			if (this == &other) return *this;

			delete[] m_data; 

			m_data = other.m_data; 
			m_size = other.m_size;

			other.m_data = nullptr;
			other.m_size = 0;

			return *this;
		}
		
		~Holder(){
			cout<<"Destructor"<<'\n';
			delete [] m_data;
		}
		
};

int main(){
	Holder h1(1000);   // Constructor comun
	Holder h2(h1);  // Constructor de movimiento
	Holder h3((Holder&&)h1); // Constructor de movimiento 
	
	h2 = h3;    //Operador de asignacion Lvalue
	h1 = (Holder&&)h3; // //Operador de asignacion Rvalue
	return 0;
}
