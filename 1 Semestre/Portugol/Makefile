all: portugol

portugol: portugol.cpp
	g++ -std=c++11 portugol.cpp -o portugol

test: all
	@mkdir -p saidas_teste
	@./portugol < testes/teste_01.por > saidas_teste/saida_01.txt
	@./portugol < testes/teste_02.por > saidas_teste/saida_02.txt
	@./portugol < testes/teste_03.por > saidas_teste/saida_03.txt
	@./portugol < testes/teste_04.por > saidas_teste/saida_04.txt
	@./portugol < testes/teste_05.por > saidas_teste/saida_05.txt
	@./portugol < testes/teste_06.por > saidas_teste/saida_06.txt
	@./portugol < testes/teste_07.por > saidas_teste/saida_07.txt
	@./portugol < testes/teste_08.por > saidas_teste/saida_08.txt
	@./portugol < testes/teste_09.por > saidas_teste/saida_09.txt
	@./portugol < testes/teste_10.por > saidas_teste/saida_10.txt

	
	@diff saidas_teste/saida_01.txt saidas_padrao/saida_teste_01.por.txt > /dev/null && echo "Teste 01: correto" || echo "Teste 01: incorreto"
	@diff saidas_teste/saida_02.txt saidas_padrao/saida_teste_02.por.txt > /dev/null && echo "Teste 02: correto" || echo "Teste 02: incorreto"
	@diff saidas_teste/saida_03.txt saidas_padrao/saida_teste_03.por.txt > /dev/null && echo "Teste 03: correto" || echo "Teste 03: incorreto"
	@diff saidas_teste/saida_04.txt saidas_padrao/saida_teste_04.por.txt > /dev/null && echo "Teste 04: correto" || echo "Teste 04: incorreto"
	@diff saidas_teste/saida_05.txt saidas_padrao/saida_teste_05.por.txt > /dev/null && echo "Teste 05: correto" || echo "Teste 05: incorreto"
	@diff saidas_teste/saida_06.txt saidas_padrao/saida_teste_06.por.txt > /dev/null && echo "Teste 06: correto" || echo "Teste 06: incorreto"
	@diff saidas_teste/saida_07.txt saidas_padrao/saida_teste_07.por.txt > /dev/null && echo "Teste 07: correto" || echo "Teste 07: incorreto"
	@diff saidas_teste/saida_08.txt saidas_padrao/saida_teste_08.por.txt > /dev/null && echo "Teste 08: correto" || echo "Teste 08: incorreto"
	@diff saidas_teste/saida_09.txt saidas_padrao/saida_teste_09.por.txt > /dev/null && echo "Teste 09: correto" || echo "Teste 09: incorreto"
	@diff saidas_teste/saida_10.txt saidas_padrao/saida_teste_10.por.txt > /dev/null && echo "Teste 10: correto" || echo "Teste 10: incorreto"

clean:
	rm -f portugol
	rm -rf saidas_teste

.PHONY: all test clean
