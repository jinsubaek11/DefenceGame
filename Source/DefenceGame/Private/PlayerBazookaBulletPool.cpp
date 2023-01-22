#include "PlayerBazookaBulletPool.h"
#include "PooledPlayerBazookaBullet.h"

APlayerBazookaBulletPool::APlayerBazookaBulletPool()
{
	classType = APooledPlayerBazookaBullet::StaticClass();
	poolSize = 5;
}