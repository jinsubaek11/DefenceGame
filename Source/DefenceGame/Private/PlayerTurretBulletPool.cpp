#include "PlayerTurretBulletPool.h"
#include "PooledPlayerTurretBullet.h"


APlayerTurretBulletPool::APlayerTurretBulletPool()
{
	classType = APooledPlayerTurretBullet::StaticClass();
	poolSize = 5;
}