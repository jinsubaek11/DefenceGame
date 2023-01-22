#include "PlayerRifleBulletPool.h"
#include "PooledPlayerRifleBullet.h"

APlayerRifleBulletPool::APlayerRifleBulletPool()
{
	classType = APooledPlayerRifleBullet::StaticClass();
	poolSize = 30;
}