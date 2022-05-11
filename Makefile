all:
	g++ -std=c++17 HangMan_2_2.cpp util.cpp draw.cpp guesser.cpp -o ./bin/HangMan_2_2
	./bin/HangMan_2_2