// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class TOONTANKS_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditDefaultsOnly, Category="Combats")
	UStaticMeshComponent *ProjectileMesh;

	UPROPERTY(VisibleAnywhere, Category="Combats")
	class  UParticleSystemComponent* ParticleSystemComponent;

	UPROPERTY(VisibleAnywhere)
	class UProjectileMovementComponent *ProjectileMovementComponent;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit );

	UPROPERTY(EditAnywhere)
	float Damage = 15.f;

	UPROPERTY(EditAnywhere)
	class UParticleSystem* ParticleSystem;
	UPROPERTY(EditAnywhere, Category="Combats")
	class USoundBase* LaunchSound;
	UPROPERTY(EditAnywhere, Category="Combats")
	 USoundBase* HitSound;
	UPROPERTY(EditAnywhere, Category="Combats")
	TSubclassOf<class UCameraShakeBase> HitCameraShake;
};
