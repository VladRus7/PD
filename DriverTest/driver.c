#include <ntddk.h>

VOID DriverUnload(PDRIVER_OBJECT pDriverObject)
{
    UNREFERENCED_PARAMETER(pDriverObject);
    DbgPrint("DriverUnload called. Unloading driver.\n");
}

NTSTATUS DriverEntry(PDRIVER_OBJECT pDriverObject, PUNICODE_STRING pRegistryPath)
{
    UNREFERENCED_PARAMETER(pRegistryPath);
    DbgPrint("DriverEntry called. Driver loaded successfully.\n");

    pDriverObject->DriverUnload = DriverUnload;

    return STATUS_SUCCESS;
}
