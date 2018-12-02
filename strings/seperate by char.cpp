vector <string> v;
string s,t;
cin >> s;
stringstream test(s);
while(getline(test,t,'.')){
    v.pb(t);
}


/*
    This code gives v.size() as 3 for aa..v with second string in vector as null
    but it doesnot give v.size() as 3 for aa.v. but it gives only two strings
*/
