// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/UI/PlayerUIComponent.h"
#include "Components/Inventory/PlayerInventoryComponent.h"
#include "Blueprint/UserWidget.h"

#include "LOP_FunctionLibrary.h"

void UPlayerUIComponent::PushWidget(FName WidgetName)
{
	UUserWidget* Widget = GetWidget(WidgetName);
	if (!Widget)
	{
		UE_LOG(LogTemp, Warning, TEXT("[UI] PushWidget failed | Widget not found: %s"), *WidgetName.ToString());
		return;
	}

	// 현재 보이는 위젯을 스택에 저장 (단, MainOverlay는 제외)
	WidgetStack.Add(WidgetName);
	UE_LOG(LogTemp, Log, TEXT("[UI] PushWidget | Pushed: %s | Current Stack Size: %d"), *WidgetName.ToString(), WidgetStack.Num());

	// 새로운 위젯 보여주기
	Widget->SetVisibility(ESlateVisibility::Visible);
	UE_LOG(LogTemp, Log, TEXT("[UI] PushWidget | Set Visible: %s"), *WidgetName.ToString());
}


bool UPlayerUIComponent::PopWidget()
{
	if (WidgetStack.Num() <= 1)
	{
		// 스택이 비어있으면 기본 PlayerOverlay로 복귀
		UUserWidget* MainWidget = GetWidget("Main");

		MainWidget->SetVisibility(ESlateVisibility::Visible);

		UE_LOG(LogTemp, Log, TEXT("[UI] PopWidget | Stack empty, showing Main"));
		for (const FName& WidgetName : WidgetStack)
		{
			if (UUserWidget* Widget = GetWidget(WidgetName))
			{
				Widget->SetVisibility(ESlateVisibility::Collapsed);
			}
		}

		WidgetStack.Empty();
		return false;
	}

	// 마지막 위젯 가져오기
	FName LastWidgetName = WidgetStack.Pop();
	UUserWidget* Widget = GetWidget(LastWidgetName);
	Widget->SetVisibility(ESlateVisibility::Collapsed);

	return true; // 정상적으로 팝 성공
}

void UPlayerUIComponent::RegisterWidget(FName WidgetName, UUserWidget* Widget)
{
	if (!Widget) return;
	WidgetMap.Add(WidgetName, Widget);
}

UUserWidget* UPlayerUIComponent::GetWidget(FName WidgetName) const
{
	if (WidgetMap.Contains(WidgetName))
	{
		return WidgetMap[WidgetName];
	}
	return nullptr;
}


TArray<FInventorySlot> UPlayerUIComponent::GetItemsByType(EItemType Type) const
{
	if (CachedInventory)
	{
		return CachedInventory->GetItemsByType(Type);
	}
	return {};
}
