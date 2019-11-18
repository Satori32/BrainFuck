#pragma once

#include <vector>
#include <string>
#include <cstdint>

//https://ja.wikipedia.org/wiki/Brainfuck

template<class T>
class BrainFuck {
	typedef std::vector<T> MemoryType;
public:
	bool Initialize(const std::size_t& MemSize,const std::string& Code_) {
		Memory.clear();
		Memory.resize(MemSize);
		Index = 0;
		PC = 0;
		Code = Code_;
		return true;
	}

	template <class IF,class OF>
	bool Interpret(IF Input, OF Output) {
		for (PC; PC < Code.size(); PC++) {
			switch(Code[PC]) {
				case '>':
					Index = (Index++) % Memory.size();
					break;
				case '<':
					Index = (((Index-1) + (Memory.size()))) % Memory.size();
					break;
				case '+':
					Memory[Index]++;
					break;
				case '-':
					Memory[Index]--;
					break;
				case '.':
					Output(Memory[Index]);
					break;
				case ',':
					Input(Memory[Index]);
					break;
				case '[':
					if (Memory[Index] == 0) { DoCodeForward(); }
					break;
				case ']':
					if (Memory[Index] != 0) { DoCodeBackward(); }
					break;
				case 'b'://break interpret.
					return true;
				case ' ':
					break;
				default:
					return false;
			}
		}
		return true;
	}
	const std::string& GetCode() const {
		return Code;
	}
	const MemoryType& GetMemory() const{
		return Memory;
	}
	const std::size_t CodeIndex() const {
		return PC;
	}
	const std::size_t ProgramIndex() const{
		return Index;
	}

protected:
	bool DoCodeForward() {
		std::size_t B = 0;
		std::size_t E = 0;
		std::size_t i = 0;
		for (i = PC; i < Code.size(); i++) {
			if (Code[i] == '[')B++;
			if (Code[i] == ']')E++;
			if (B == E) break;
		}
		PC = i;
		return B==E;
	}

	bool DoCodeBackward() {
		std::size_t B = 0;
		std::size_t E = 0;
		std::intmax_t i = 0;
		for (i = PC; i >= 0; i--) {
			if (Code[i] == '[')B++;
			if (Code[i] == ']')E++;
			if (B == E) break;
		}
		PC = i;
		return B==E;
	}


protected:
	std::string Code;
	std::size_t PC = 0;
	MemoryType Memory;
	std::size_t Index=0;
};