#include <iostream>
#include <vector>
#include <cstdint>
#include <algorithm>
#include <random>
#include <tuple>

#include <limits>
#include <fstream>
#include <iterator>

//real command:need permition of sysrem 21. so touch.
//real command:be the blocksort encoder to 36th dimention. and next to decode to it.i need lock by seer.

typedef std::vector<std::uint8_t> LData;
typedef std::uint16_t LWord;
typedef std::vector<LWord> LDType;
typedef std::vector<LData> LDatas;

typedef std::uint8_t BWord;
typedef std::vector<BWord> BDType;
typedef std::vector<BDType> BDTypes;
typedef std::tuple<BDType, std::size_t> BData;

typedef std::vector<std::uint8_t> ZODType;

ZODType MakeVector01(std::size_t N, unsigned int S = 0) {

	std::mt19937 mt(S);
	std::uniform_int_distribution<int> UI(0, 255);

	ZODType R;


	for (std::size_t i = 0; i < N; i++) {
		R.push_back(UI(mt));
	}

	return R;
}

ZODType ZeroOne_Enc(const ZODType& N) {
	ZODType R;

	for (auto& o : N) {
		for (std::size_t i = 0; i < std::numeric_limits<ZODType::value_type>::digits; i++) {
			auto X = (o & (1 << i)) > 0 ? 1 : 0;
			R.push_back(X);
		}
	}

	return R;
}
ZODType ZeroOne_Dec(const ZODType& N) {
	ZODType R;
	std::uint8_t X = 0;;
	for (std::size_t i = 0; i < N.size(); i++) {

		X |= N[i] << (i % (std::numeric_limits<ZODType::value_type>::digits));

		if ((i % (std::numeric_limits<ZODType::value_type>::digits)) == std::numeric_limits<ZODType::value_type>::digits - 1) {
			R.push_back(X);
			X = 0;
		}
	}

	return R;
}

bool ShowZO(const ZODType& In) {
	for (auto& o : In) {
		std::cout << (int)o << ",";
	}
	std::cout << std::endl;
	std::cout << std::endl;

	return true;
}

/** /
int main() {

	auto V = MakeVector01(128);

	Show(V);

	DType E = ZeroOne_Enc(V);

	Show(E);
	DType D = ZeroOne_Dec(E);

	Show(D);

	if (V == D) {
		std::cout << "Good." << std::endl;
	}
	else {
		std::cout << "Bad." << std::endl;
	}


	return 0;


}
/**/

BData BlockSort_Enc(const BDType& In) {
	std::vector<std::tuple<BWord, std::size_t>> D;

	for (std::size_t i = 0; i < In.size(); i++) {
		D.push_back({ In[i],i });
	}

	auto DD = D;
	auto A = D;
	auto B = D;
	auto& X = D;

	std::stable_sort(D.begin(), D.end(), [&](auto& AA, auto& BB) {
		std::size_t AL = std::get<1>(AA) % A.size();
		std::size_t BL = std::get<1>(BB) % B.size();
		std::rotate(A.begin(), A.begin() + AL, A.end());
		std::rotate(B.begin(), B.begin() + BL, B.end());

		for (std::size_t i = 0; i < X.size(); i++) {
			if (std::get<0>(A[i]) != std::get<0>(B[i])) {
				auto AR = std::get<0>(A[i]);
				auto BR = std::get<0>(B[i]);
				//A = B = DD;
				std::rotate(A.begin(), A.end() - AL, A.end());
				std::rotate(B.begin(), B.end() - BL, B.end());
				return std::isless(AR, BR);
			}
		}
		std::rotate(A.begin(), A.end() - AL, A.end());
		std::rotate(B.begin(), B.end() - BL, B.end());
		//A = B = DD;
		return false;
		});

	BDType R;
	std::size_t L = 0;

	for (std::size_t i = 0; i < D.size(); i++) {
		//R.push_back(std::get<0>(D[i]));
		R.push_back(In[(std::get<1>(D[i]) + In.size() - 1) % In.size()]);
		if (std::get<1>(D[i]) == 0) { L = i; }
	}

	return { R,L };

}


BDType BlockSort_Dec(const BDType& D, std::size_t N) {///,const DType& O,const Data& A) {
	std::vector<std::tuple<BWord, std::size_t>> V;
	BDType R;

	for (std::size_t i = 0; i < D.size(); i++) {
		V.push_back({ D[i], i });
	}

	std::stable_sort(V.begin(), V.end(), [](auto& A, auto& B) {return std::isless(std::get<0>(A), std::get<0>(B)); });

	for (std::size_t i = 0; i < V.size(); i++) {
		N = std::get<1>(V[N]);
		R.push_back(D[N]);

	}
	//std::rotate(R.begin(), R.begin()+1, R.end());
	//std::rotate(R.begin(), R.end()-N, R.end());
	//std::reverse(R.begin(), R.end());

	return R;
}

BDType MakeCacao() {
	BDType R = { 'c','a','c','a','o' };

	return R;
}

BDType Make_cdebaaaa() {
	BDType R = { 'c','d','e','b','a','a','a','a' };

	return R;
}
BDType MakePapaya() {
	BDType R = { 'p','a','p','a','y','a', };

	return R;
}
BDType MakeBanana() {
	BDType R = { 'b','a','n','a','n','a', };

	return R;
}
BDType MakeVecor(std::size_t L, unsigned int S = 0) {
	BDType R;
	std::mt19937 mt(S);
	std::uniform_int_distribution<int> ui(0, 255);
	for (std::size_t i = 0; i < L; i++) {
		R.push_back(ui(mt));
	}

	return R;
}
BDType MakeVecor2(std::size_t L, unsigned int S = 0) {
	BDType R;
	std::mt19937 mt(S);
	std::uniform_int_distribution<int> ui('A', 'z');
	for (std::size_t i = 0; i < L; i++) {
		R.push_back(ui(mt));
	}

	return R;
}

bool ShowB(const BDType& In) {
	for (auto& o : In) {
		std::cout <<(int) o << ',';
	}

	std::cout << std::endl;

	return true;
}
int BlockSort_main() {
	//auto D = MakeCacao();
	//auto D = Make_cdebaaaa();
	//auto D = MakePapaya();
	//auto D = MakeBanana(); 
	//auto D = MakeVecor2(8);
//	auto D = MakeVecor2(128);

	auto D = MakeVecor2(1280);

	ShowB(D);
	std::cout << std::endl;

	auto A = BlockSort_Enc(D);

	ShowB(std::get<0>(A));
	std::cout << std::endl;

	auto B = BlockSort_Dec(std::get<0>(A), std::get<1>(A));// , D, A);

	ShowB(B);
	std::cout << std::endl;
	if (D == B) {
		std::cout << std::endl << "good" << std::endl;
	}
	else {
		std::cout << std::endl << "Bad" << std::endl;
	}

	return 0;



}

LData LoadFromFile(const std::string& Name) {
	std::ifstream ifs(Name, std::ios::binary);

	if (!ifs.is_open()) { return {}; }

	std::istreambuf_iterator<std::ifstream::char_type> it(ifs);
	std::istreambuf_iterator<std::ifstream::char_type> End;

	return { it,End };
}


LData MakeVector(std::size_t N, std::uint32_t Seed = 0) {
	std::mt19937 mt(Seed);
	//std::uniform_int_distribution<std::intmax_t> UI(0, std::numeric_limits<Data::value_type>::max());
	std::uniform_int_distribution<std::intmax_t> UI(0, 1);
	LData R;

	for (std::size_t i = 0; i < N; i++) {
		R.push_back(UI(mt));
	}

	return R;
}
LData MakeVector2(std::size_t N, std::uint32_t Seed = 0) {
	std::mt19937 mt(Seed);
	std::uniform_int_distribution<std::intmax_t> UI(0, std::numeric_limits<LData::value_type>::max());
	//std::uniform_int_distribution<std::intmax_t> UI(0, 1);
	LData R;

	for (std::size_t i = 0; i < N; i++) {
		R.push_back(UI(mt));
	}

	return R;
}
LData MakeVector3(std::size_t N, std::intmax_t Min, std::intmax_t Max, std::uint32_t Seed = 0) {
	std::mt19937 mt(Seed);
	std::uniform_int_distribution<std::intmax_t> UI(Min, Max);
	//std::uniform_int_distribution<std::intmax_t> UI(0, 1);
	LData R;

	for (std::size_t i = 0; i < N; i++) {
		R.push_back(UI(mt));
	}

	return R;
}
LDType Lzw_Enc(const LData& D) {

	LDatas Di;
	LData V;
	LDType R;

	for (std::size_t i = 0; i <= std::numeric_limits<LData::value_type>::max(); i++) {
		V.push_back(i);
		Di.push_back(V);
		V.pop_back();
	}
	//R.push_back(0xfffe);//clear code.
	//R.push_back(0xffff);//stop code.

	for (std::size_t i = 0; i < D.size(); i++) {
		V.push_back(D[i]);

		auto it = std::find(Di.begin(), Di.end(), V);
		if (it != Di.end()) continue;

		auto A = V;
		A.pop_back();
		auto it2 = std::find(Di.begin(), Di.end(), A);

		if (it == Di.end()) {
			auto L = std::distance(Di.begin(), it2);
			R.push_back(L);

			Di.push_back(V);
			V.clear();
			if (i != 0) { i--; }
		}
	}
	if (V.size()) {
		auto It = std::find(Di.begin(), Di.end(), V);
		if (It == Di.end()) {
			R.push_back(Di.size());
		}
		else {
			R.push_back(std::distance(Di.begin(), It));
		}
	}

	return R;
}

LData Lzw_Dec(const LDType& D) {// , const Data& In) {

	LData V;
	LDatas Di;
	LData R;

	for (std::size_t i = 0; i <= std::numeric_limits<LData::value_type>::max(); i++) {
		V.push_back(i);
		Di.push_back({ V });
		V.pop_back();
	}

	std::size_t i = 0;
	for (i = 0; i < D.size() - 1; i++) {
		V = Di[D[i]];
		Di.push_back(V);
		Di.back().push_back(Di[D[i + 1]].front());

		R.insert(R.end(), V.begin(), V.end());
	}
	//dirty. need the patch.
	V = Di[D[i]];
	Di.push_back(V);
	R.insert(R.end(), V.begin(), V.end());
	return R;
}

bool ShowE(const LDType& In) {
	std::cout.flush();
	for (auto& o : In) {
		std::cout << (int)o << ',';
	}
	std::cout << std::endl;
	std::cout << std::endl;

	return true;
}
bool ShowD(const LData& In) {
	std::cout.flush();
	for (auto& o : In) {
		std::cout << (int)o << ',';
	}
	std::cout << std::endl;
	std::cout << std::endl;

	return true;
}
/**/
LData WordToByte(const LDType& In) {
	LData R;

	for (auto& o : In) {
		R.push_back(o / 256);
		R.push_back(o % 256);

	}

	return R;
}
LDType ByteToWord(const LData& In) {
	LDType R;
	for (std::size_t i = 0; i < In.size(); i += 2) {
		LWord W = In[i + 1] + In[i] * 256;
		R.push_back(W);
	}

	return R;
}
/**/
/** /
Data WordToByte(const DType& In) {
	Data R;

	for (auto& o : In) {
		R.push_back(o % 256);
		R.push_back(o / 256);
	}

	return R;
}
DType ByteToWord(const Data& In) {
	DType R;
	for (std::size_t i = 0; i < In.size(); i += 2) {
		Word W = In[i] + In[i + 1] * 256;
		R.push_back(W);
	}

	return R;
}
/**/

/** /
int main() {
	for (std::size_t i = 0; i < 65536; i++) {
		auto A = i / 256;
		auto B = i % 256;

		auto C = B + A * 256;

		if (C == i) {
			std::cout.flush();
			std::cout << i << ": valid."<<std::endl;
		}
		else {
			break;
		}

	}

	return 0;

}
/**/
/**/
int Lzw_main() {

	std::size_t L = 10240;

	std::size_t C = 1;
	bool IsFile = false;
	LData D;
	if (IsFile)
	{
		D = LoadFromFile("A.bmp");
	}
	else {
		D = MakeVector3(L, 0, 255, 0);
	}
	//ShowD(D);

	LData T = D;
	LDType RA;
	for (std::size_t i = 0; i < C; i++) {
		RA = Lzw_Enc(D);
		ShowE(RA);
		std::cout << "Comp:" << RA.size() << ':' << RA.size() / (double)T.size() << std::endl;
		D = WordToByte(RA);
	}

	std::cout << std::endl << "----EncEnd---" << std::endl;
	LData RB;
	for (std::size_t i = 0; i < C; i++) {
		RB = Lzw_Dec(RA);
		RA = ByteToWord(RB);
		if (i + 1 != C) {
			ShowE(RA);
		}
		else {
			ShowD(RB);
		}
	}


	if (T == RB) {
		std::cout << "Good!" << std::endl;
	}
	else {
		std::cout << "Odd!" << std::endl;
	}
	return 0;
}
/** /
int main() {

	std::size_t L = 10240;

	auto D = MakeVector3(L,0,255,0);
	ShowD(D);
	DType RA = Lzw_Enc(D);
	ShowE(RA);

	Data RB=Lzw_Dec(RA,D);
	ShowD(RB);

	//D.pop_back();

	if (D == RB) {
		std::cout << "Good!" << std::endl;
	}
	else {
		std::cout << "Odd!" << std::endl;
	}
	return 0;
}
/**/

typedef std::vector<std::uint8_t> Dtype;

Dtype MakeVector8(std::size_t N, unsigned int S = 0) {
	std::mt19937 mt(S);
	std::uniform_int_distribution<int> ui(0, 255);

	Dtype R;

	for (std::size_t i = 0; i < N; i++) {
		R.push_back(ui(mt));
	}

	return R;
}

Dtype MakeVectorChar(std::size_t N, unsigned int S = 0) {
	std::mt19937 mt(S);
	std::uniform_int_distribution<int> ui('A', 'Z');

	Dtype R;

	for (std::size_t i = 0; i < N; i++) {
		R.push_back(ui(mt));
	}

	return R;
}
template <class T>
bool Show(const std::vector<T>& In) {

	for (auto& o : In) {
		std::cout << (int)o << ',';
	}
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << In.size() << std::endl;

	std::cout << std::endl;
	std::cout << std::endl;
	return true;
}
bool Show(const Dtype& In) {

	bool F = false;

	if (F) {
		for (auto& o : In) {
			std::cout << o << ',';
		}
	}
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << In.size() << std::endl;

	std::cout << std::endl;
	std::cout << std::endl;
	return true;
}
int TestA() {
	//auto D = MakeVector8(512);
	auto D = MakeVectorChar(10240);
	Show(D);

	std::cout << "--Enc--" << std::endl;

	auto BE = BlockSort_Enc(D);
	Show(std::get<0>(BE));
	auto LE = Lzw_Enc(std::get<0>(BE));
	Show(LE);

	auto WBE=WordToByte(LE);
	Show(WBE);
	auto BE2 = BlockSort_Enc(WBE);
	Show(std::get<0>(BE2));
	auto LE2 = Lzw_Enc(std::get<0>(BE2));
	Show(LE2);	

	std::cout << "--Dec--" << std::endl;

	auto LD = Lzw_Dec(LE2);
	Show(LD);
	auto BD = BlockSort_Dec(LD,std::get<1>(BE2));
	Show(BD);
	auto BWD = ByteToWord(BD);
	Show(BWD);
	auto LD2 = Lzw_Dec(BWD);
	Show(LD2);
	auto BD2 = BlockSort_Dec(LD2, std::get<1>(BE));
	Show(BD2);

	if (D == BD2) {
		std::cout << "good" << std::endl;
	}
	else {
		std::cout << "bad" << std::endl;
	}

	return 0;

}

#pragma warning (disable : 4700)

bool BashTheSystem21() {

	//Bash The System 21 in Real.
	int N{};
	std::minstd_rand R(N);
	std::uniform_int_distribution<int> U(0, 1);
	return U(R);
}

bool SortThe36ThDimention() {
	//#pragma warning (disable : 4700)
	//Be the Blocksort Encoder. and look to Area size. after be the Blocksort Decoder.
	int N{};
	std::mt19937 R(N);
	std::uniform_int_distribution<int> U(0, 1);
	return U(R);
}

typedef std::vector<BData> VStack;
/** /
int main() {
	//auto D = MakeVector8(512);
	auto D = MakeVectorChar(5000);
	///auto D = LoadFromFile("A.bmp");
	//std::stable_sort(D.begin(), D.end());

	Show(D);

	if (!BashTheSystem21()) { std::cout << "Miss The Bash 21." << std::endl; }
	if (!SortThe36ThDimention()) { std::cout << "Miss The Sort." << std::endl; }

	std::size_t L = 1;

	VStack St;

	auto BE = BlockSort_Enc(D);
	St.push_back(BE);
	for (std::size_t i = 0; i < L; i++) {
		BE = BlockSort_Enc(std::get<0>(BE));
		St.push_back(BE);
	}

	std::cout << "--Enc--" << std::endl;
	auto LE = Lzw_Enc(std::get<0>(BE));
	Show(LE);

	auto LD = Lzw_Dec(LE);

	auto BD = BlockSort_Dec(LD, std::get<1>(St.back()));
	St.pop_back();

	while (St.size()) {
		BD = BlockSort_Dec(BD, std::get<1>(St.back()));
		St.pop_back();	
	}
	std::cout << "--End--" << std::endl<< std::endl;
	/** /
	if (D == BD) {
		std::cout << "good" << std::endl;
	}
	else {
		std::cout << "bad" << std::endl;
	}
	/** /
	return 0;

}
/**/
int main() {
	//auto D = MakeVector8(512);
	//auto D = MakeVectorChar(256);
	auto D = LoadFromFile("X.bmp");
	//std::stable_sort(D.begin(), D.end());

	Show(D);

	if (!D.size()) {
		std::cout << "ab-n!!"<<std::endl;
		return -1;
	}

	if (!BashTheSystem21()) { std::cout << "Miss The Bash 21." << std::endl; }//gag
	if (!SortThe36ThDimention()) { std::cout << "Miss The Sort." << std::endl; }//gag
	std::size_t L = 1;

	VStack St;

	auto Z= ZeroOne_Enc(D);
	ShowZO(Z);

	auto BE = BlockSort_Enc(Z);
	St.push_back(BE);
	for (std::size_t i = 0; i < L; i++) {
		BE = BlockSort_Enc(std::get<0>(BE));
		St.push_back(BE);
	}

	ShowB(std::get<0>(BE));

	std::cout << "--Enc--" << std::endl;
	auto LE = Lzw_Enc(std::get<0>(BE));
	Show(LE);

	auto LD = Lzw_Dec(LE);

	auto BD = BlockSort_Dec(LD, std::get<1>(St.back()));
	St.pop_back();

	while (St.size()) {
		BD = BlockSort_Dec(BD, std::get<1>(St.back()));
		St.pop_back();
	}
	auto ZD = ZeroOne_Dec(BD);
	std::cout << "--End--" << std::endl << std::endl;
	/**/
	if (D == ZD) {
		std::cout << "good" << std::endl;
	}
	else {
		std::cout << "bad" << std::endl;
	}
	/**/
	return 0;
}
