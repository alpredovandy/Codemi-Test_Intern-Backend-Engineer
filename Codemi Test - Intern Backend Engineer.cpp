#include<bits/stdc++.h>
#include<map>
#include<queue>
#include<vector>
using namespace std;
//tipe data buatan
struct loker{
	int nomor;
	string tipe;
	string id;
};

bool init=false;				//mengecek apakah jumlah loker sudah diinput
string opsi, in_tipe, in_id;	//inputan
int in_nomor;					//inputan
int jumlah=0;					//jumlah loker

map<string,int> identitas;
/*
Tipe struktur data: Binary Search Tree / TreeMap (Java)
Digunakan pada 	  : instruksi find [nomor identitas]
Alasan penggunaan :
- Mampu mendapatkan informasi nomor loker melalui nomor identitas dengan cepat O(log N)
- Jika menggunakan array, maka setiap proses membutuhkan waktu yang lebih lama O(N)
*/

priority_queue<int,vector<int>,greater<int> > no_loker;
/*
Tipe struktur data: Priority Queue versi Minimum / Heap
Digunakan pada	  : input [tipe identitas] [nomor identitas]
					leave [nomor loker]
Alasan penggunaan :
- Menyediakan nomor loker yang tersedia untuk pengguna dengan cepat O(log N)
- Ketika terdapat instruksi 'input', struktur data akan memberikan nomor loker terkecil
  dan menghapusnya dari struktur data
- Ketika terdapat instruksi 'leave', struktur data akan memasukkan kembali nomor loker
  untuk digunakan kembali
*/
vector<loker> data; //array dari tipe data loker

//mengubah string menjadi lowercase karena inputan bersifat case insensitive
string tolower(string str)
{
	for(int i=0;i<str.length();++i)
		str[i]=tolower(str[i]);
	return str;
}

//menampilkan isi loker yang sedang digunakan
void printStatus()
{
	printf("No Loker \t Tipe Identitas  No Identitas\n");
	for(int i=0;i<jumlah;++i)
		if(data[i].nomor)
			printf("%d \t\t %s \t\t %s\n",data[i].nomor,data[i].tipe.c_str(),data[i].id.c_str());
}

//memberikan bantuan
void peringatan()
{
	printf("Perintah yang tersedia adalah\n");
	printf("init [jumlah loker]\n");
	printf("status\n");
	printf("input [tipe identitas] [nomor identitas]\n");
	printf("leave [nomor loker]\n");
	printf("exit\n\n");
}

//mengecek apakah instruksi yang diinputkan benar
bool opsi_benar(string str)
{
	if(str=="init" || str=="status" || str=="input" || str=="leave" || str=="find" || str=="exit")
		return true;
	return false;
}

int main()
{
	do
	{
		cin>>opsi;
		opsi=tolower(opsi);
		if(!opsi_benar(opsi))	peringatan();
		else if(opsi=="init")
		{
			cin>>jumlah;
			data.assign(jumlah,{});							//inisialisasi array
			while(!no_loker.empty())	no_loker.pop();		//membersihkan no_loker
			for(int i=1;i<=jumlah;++i)	no_loker.push(i);	//memasukkan semua no_loker yang tersedia
			printf("Berhasil membuat loker dengan jumlah %d\n",jumlah);
			init=true;
		}
		else if(!init)
		{
			getline(cin,opsi);	//membersihkan inputan
			printf("Jumlah loker belum ditentukan\n");
		}
		else if(opsi=="status")	printStatus();
		else if(opsi=="input")
		{
			cin>>in_tipe>>in_id;
			if(no_loker.empty())	printf("Maaf loker sudah penuh\n");
			else
			{
				in_nomor=no_loker.top();no_loker.pop();		//mengambil dan menghapus nomor loker
				data[in_nomor-1]={in_nomor,in_tipe,in_id};	//memasukkan data ke dalam array
				identitas[in_id]=in_nomor;					//memasukkan info ke BST
				printf("Kartu identitas tersimpan di loker nomor %d\n",in_nomor);
			}
		}
		else if(opsi=="leave")
		{
			cin>>in_nomor;
			loker hapus=data[in_nomor-1];
			if(identitas.find(hapus.id)==identitas.end())	//jika identitas tidak terdaftar
				printf("Loker nomor %d kosong\n",in_nomor);
			else
			{
				identitas.erase(hapus.id);					//menghapus dari BST
				data[in_nomor-1]={};						//mengosongkan 1 loker
				no_loker.push(in_nomor);					//nomor loker bisa digunakan kembali
				printf("Loker nomor %d berhasil dikosongkan\n",in_nomor);
			}
		}
		else if(opsi=="find")
		{
			cin>>in_id;
			if(identitas.find(in_id)==identitas.end())
				printf("Kartu identitas tersebut tidak ada dalam loker\n");
			else
				printf("Kartu identitas tersebut berada di loker nomor %d\n",identitas[in_id]);
		}
	}while(opsi!="exit");
}
