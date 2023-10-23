#include "common.h"

IN_ADDR GetDefaultMyIP()
{
	char localhostname[MAX_PATH];
	IN_ADDR addr = { 0, };

	//gethostname�� ���� ��ǻ���� ǥ�� ȣ��Ʈ �̸��� �˻��� -> 
	// 1. ������ SOKET_ERROR�� ��ȯ�ϰ� ��� ���������Դ��� �� �� ����
	// 2. ������ �߻����� ������ 0�� ��ȯ

	int result = gethostname(localhostname, MAX_PATH);

	if (result == SOCKET_ERROR)
	{
		// GETHOSTNAME ���н� ������ ���� ���� �����ڵ�� �˷���
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
