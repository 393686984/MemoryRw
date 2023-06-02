#include "DriverRw.h"
#include "CommIo.h"

extern NTSTATUS NTAPI MmCopyVirtualMemory(
	PEPROCESS FromProcess,
	PVOID FromAddress,
	PEPROCESS ToProcess,
	PVOID ToAddress,
	SIZE_T BufferSize,
	KPROCESSOR_MODE PreviousMode,
	PSIZE_T NumberOfBytesCopied
);
NTSTATUS DriverIrpCtl(PDEVICE_OBJECT pDevice, PIRP pIrp)
{
	NTSTATUS status = 0;
	ULONG byTest = 0;
	PIO_STACK_LOCATION pStack = IoGetCurrentIrpStackLocation(pIrp);

	ULONG ulCode = pStack->Parameters.DeviceIoControl.IoControlCode;

	switch (ulCode)
	{
	case READCODE: {//¶ÁÄÚ´æ
		PReadInfo Info = (PReadInfo)pIrp->AssociatedIrp.SystemBuffer;

		PEPROCESS Process = 0;

		NTSTATUS Result = PsLookupProcessByProcessId((HANDLE)Info->ProcessID, &Process);

		if (NT_SUCCESS(Result))
		{
			ReadMemory(Process, (PVOID)Info->pSource, (PVOID)Info->pTarget, Info->Size);
		}
		byTest = sizeof(PReadInfo);
		status = STATUS_SUCCESS;
		break;
	}
	case WRITECODE: {
		PWriteInfo Info = (PWriteInfo)pIrp->AssociatedIrp.SystemBuffer;

		PEPROCESS Process = 0;

		NTSTATUS Result = PsLookupProcessByProcessId((HANDLE)Info->ProcessID, &Process);

		if (NT_SUCCESS(Result))
		{
			WriteMemory(Process, (PVOID)Info->pSource, (PVOID)Info->pTarget, Info->Size);

		}
		byTest = sizeof(PWriteInfo);
		status = STATUS_SUCCESS;
		break;
	}
	default: {
		status = STATUS_INVALID_PARAMETER;
		break;
	}

	}
	pIrp->IoStatus.Status = status;
	pIrp->IoStatus.Information = byTest;
	IoCompleteRequest(pIrp, IO_NO_INCREMENT);
	return status;

}

NTSTATUS CreateDriver(PDEVICE_OBJECT pDevice, PIRP pIrp)
{
	pIrp->IoStatus.Status = STATUS_SUCCESS;
	pIrp->IoStatus.Information = 0;

	IoCompleteRequest(pIrp, IO_NO_INCREMENT);
	return STATUS_SUCCESS;
}
NTSTATUS CloseDriver(PDEVICE_OBJECT pDevice, PIRP pIrp)
{
	pIrp->IoStatus.Status = STATUS_SUCCESS;
	pIrp->IoStatus.Information = 0;

	IoCompleteRequest(pIrp, IO_NO_INCREMENT);
	return STATUS_SUCCESS;

}



NTSTATUS ReadMemory(PEPROCESS Process, PVOID SourceAddress, PVOID TargetAddress, SIZE_T Size)
{
	SIZE_T Bytes;
	if (NT_SUCCESS(MmCopyVirtualMemory(Process, SourceAddress, PsGetCurrentProcess(), TargetAddress, Size, KernelMode, &Bytes)))
	{
		return STATUS_SUCCESS;

	}
	else {
		return STATUS_ACCESS_DENIED;
	}
}

NTSTATUS WriteMemory(PEPROCESS Process, PVOID SourceAddress, PVOID TargetAddress, SIZE_T Size)
{
	SIZE_T Bytes;
	if (NT_SUCCESS(MmCopyVirtualMemory(PsGetCurrentProcess(), SourceAddress, Process, TargetAddress, Size, KernelMode, &Bytes)))
	{
		return STATUS_SUCCESS;

	}
	else {
		return STATUS_ACCESS_DENIED;
	}
}
