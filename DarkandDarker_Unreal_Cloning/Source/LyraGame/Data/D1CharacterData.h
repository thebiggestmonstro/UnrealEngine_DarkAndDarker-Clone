// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "D1Define.h"
#include "Engine/DataAsset.h"
#include "D1CharacterData.generated.h"

USTRUCT(BlueprintType)
struct FD1DefaultArmorMeshSet
{
	GENERATED_BODY()

public:
	// 상체 머티리얼
	UPROPERTY(EditDefaultsOnly)
	TSoftObjectPtr<UMaterialInterface> UpperBodySkinMaterial;

	// 하체 머티리얼
	UPROPERTY(EditDefaultsOnly)
	TSoftObjectPtr<UMaterialInterface> LowerBodySkinMaterial;

public:
	// 머리에 대한 기본 메쉬1
	UPROPERTY(EditDefaultsOnly)
	TSoftObjectPtr<USkeletalMesh> HeadDefaultMesh;

	// 머리에 대한 기본 메쉬2
	UPROPERTY(EditDefaultsOnly)
	TSoftObjectPtr<USkeletalMesh> HeadSecondaryMesh;

public:
	// 기본 장비에 대한 메쉬1
	UPROPERTY(EditDefaultsOnly, meta = (ArraySizeEnum = "EArmorType"))
	TSoftObjectPtr<USkeletalMesh> DefaultMeshEntries[(int32)EArmorType::Count];

	// 기본 장비에 대한 메쉬2
	UPROPERTY(EditDefaultsOnly, meta = (ArraySizeEnum = "EArmorType"))
	TSoftObjectPtr<USkeletalMesh> SecondaryMeshEntries[(int32)EArmorType::Count];
};

/**
 * 
 */
UCLASS()
class LYRAGAME_API UD1CharacterData : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	static const UD1CharacterData& Get();

public:
	// PreSave는 UObject를 저장하기 위해 직렬화하기 이전에 호출되는 함수, 
	// 여기서는 D1CharacterData의 DefaultArmorMeshMap에 저장된 Value를 Key값에 정렬하는데 사용
	// 이때 수행은 에디터에서만 진행함
#if WITH_EDITOR
	virtual void PreSave(FObjectPreSaveContext ObjectSaveContext) override;
#endif // WITH_EDITOR

public:
	// 인종에 대한 기본적인 장비셋을 가져오는 함수
	const FD1DefaultArmorMeshSet& GetDefaultArmorMeshSet(ECharacterSkinType CharacterSkinType) const;
	
private:
	UPROPERTY(EditDefaultsOnly)
	TMap<ECharacterSkinType, FD1DefaultArmorMeshSet> DefaultArmorMeshMap;
};
