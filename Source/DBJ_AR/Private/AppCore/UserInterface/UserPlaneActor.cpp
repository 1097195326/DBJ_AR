#include "UserPlaneActor.h"


void AUserPlaneActor::TickActor(float DeltaTime, enum ELevelTick TickType, FActorTickFunction& ThisTickFunction)
{
	Super::TickActor(DeltaTime, TickType, ThisTickFunction);

	/*TArray<UARPlaneGeometry*> planeGeometryArray = UARBlueprintLibrary::GetAllTrackedPlanes();
	if (planeGeometryArray.Num() > 0)
	{
		for (UARPlaneGeometry * planeGeometry : planeGeometryArray)
		{
			planeGeometry->getex
		}
	}*/
}