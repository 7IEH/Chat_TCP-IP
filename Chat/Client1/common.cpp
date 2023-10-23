#include "common.h"

IN_ADDR GetDefaultMyIP()
{
	char localhostname[MAX_PATH];
	IN_ADDR addr = { 0, };

	//gethostname은 로컬 컴퓨터의 표준 호스트 이름을 검색함 -> 
	// 1. 에러시 SOKET_ERROR를 반환하고 어떠한 오류가나왔는지 알 수 있음
	// 2. 오류가 발생하지 않으면 0을 반환

	int result = gethostname(localhostname, MAX_PATH);

	if (result == SOCKET_ERROR)
	{
		// GETHOSTNAME 실패시 에러가 나는 이유 에러코드로 알려줌
		int hresult = WSAGetLastError();
		return addr;
	}
	HOSTENT* ptr = gethostbyname(localhostname);

	while (ptr && ptr->h_name)
	{
		if (ptr->h_addrtype == PF_INET)
		{
			memcpy(&addr, ptr->h_addr_list[0], ptr->h_length);
			break;
		}
		ptr++;
	}
	return addr;
}
