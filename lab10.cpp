//polimorfism la compilare - in momentul compilarii
// operatori, functii cu acelasi nume si parametrii diferiti, clase tamplate
//polimorfism de rulare - in mometul rularii 
// functii virtuale cate trimit prin pointer catre alta functie(overwritten)
// SE INTAMPLA CU AJUTORUL TABELEI A METODELOR VIRTUALE
//Tabela metodelor virtuale (VMT - virtual method table)
// se tine ca un pointer cu toate functiile virtuale (creste size)
// 
// functie pur viruala:
//	se scrie =0; dar nu e definita
//	se foloseste ca  un fel de tamplate - clasa abstracta
//