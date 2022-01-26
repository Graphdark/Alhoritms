bool prime(long long n){ 
	for(long long i=2;i<=sqrt(n);i++)
		if(n%i==0)
			return false;
	return true;
}
