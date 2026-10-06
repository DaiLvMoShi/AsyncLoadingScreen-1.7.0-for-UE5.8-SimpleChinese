/************************************************************************************
 *																					*
 * Copyright (C) 2020 Truong Bui.													*
 * Website:	https://github.com/truong-bui/AsyncLoadingScreen						*
 * Licensed under the MIT License. See 'LICENSE' file for full license information. *
 *																					*
 ************************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "MoviePlayer.h"
#include "Widgets/Layout/SScaleBox.h"
#include "Styling/SlateBrush.h"
#include "Styling/SlateTypes.h"
#include "Framework/Text/TextLayout.h"
#include "LoadingScreenSettings.generated.h"


/**
 * 异步加载画面布局类型
 */
UENUM(BlueprintType)
enum class EAsyncLoadingScreenLayout : uint8
{
	/**
	 * 经典布局是一种简单通用的布局，适配多种设计风格。
	 * 加载控件和提示控件可以位于屏幕底部或顶部。
	 */
	ALSL_Classic UMETA(DisplayName = "经典"),
	/**
	 * 加载控件位于屏幕中央，提示控件可以在底部或顶部。
	 * 如果加载图标是主要视觉元素，居中布局是不错的选择。
	 */
	ALSL_Center UMETA(DisplayName = "居中"),
	/**
	 * 信箱模式在屏幕上下各有一条边框。加载控件可以在上边，
	 * 提示文本在下边，反之亦然。
	 */
	 ALSL_Letterbox UMETA(DisplayName = "信箱模式"),
	/**
	 * 侧边栏布局在屏幕左侧或右侧有一条垂直边框。
	 * 由于提示控件较高，侧边栏适合用于故事叙述、长文本展示。
	 */
	 ALSL_Sidebar UMETA(DisplayName = "侧边栏"),

	/**
	 * 与侧边栏类似，但双侧边栏在屏幕左右两侧各有一条垂直边框。
	 * 双侧边栏适合用于故事叙述、长文本展示。
	 */
	 ALSL_DualSidebar UMETA(DisplayName = "双侧边栏")
};

/** 加载图标类型 */
UENUM(BlueprintType)
enum class ELoadingIconType : uint8
{
	/** SThrobber 进度条控件 */
	LIT_Throbber UMETA(DisplayName = "进度条"),
	/** SCircularThrobber 圆形进度条控件 */
	LIT_CircularThrobber UMETA(DisplayName = "圆形进度条"),
	/** 动画图片序列 */
	LIT_ImageSequence UMETA(DisplayName = "图片序列")
};

/** 加载控件布局方向 */
UENUM(BlueprintType)
enum class ELoadingWidgetType : uint8
{
	/** 水平排列 */
	LWT_Horizontal UMETA(DisplayName = "水平"),
	/** 垂直排列 */
	LWT_Vertical UMETA(DisplayName = "垂直"),
};

/** 控件对齐方式 */
USTRUCT(BlueprintType)
struct FWidgetAlignment
{
	GENERATED_BODY()
	/** 控件的水平对齐方式 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "对齐设置", meta=(DisplayName="水平对齐"))
	TEnumAsByte<EHorizontalAlignment> HorizontalAlignment = EHorizontalAlignment::HAlign_Center;

	/** 控件的垂直对齐方式 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "对齐设置", meta=(DisplayName="垂直对齐"))
	TEnumAsByte<EVerticalAlignment> VerticalAlignment = EVerticalAlignment::VAlign_Center;
};

// 文本外观设置
USTRUCT(BlueprintType)
struct FTextAppearance
{
	GENERATED_BODY()

	/** 文本颜色与不透明度 */
	UPROPERTY(BlueprintReadWrite, Config, EditAnywhere, Category = "文本外观", meta=(DisplayName="颜色与不透明度"))
	FSlateColor ColorAndOpacity = FSlateColor(FLinearColor::White);

	// 渲染文本所用的字体
	UPROPERTY(BlueprintReadWrite, Config, EditAnywhere, Category = "文本外观", meta=(DisplayName="字体"))
	FSlateFontInfo Font;

	/** 阴影偏移量（像素） */
	UPROPERTY(BlueprintReadWrite, Config, EditAnywhere, Category = "文本外观", meta=(DisplayName="阴影偏移"))
	FVector2D ShadowOffset = FVector2D::ZeroVector;

	/** 阴影颜色与不透明度 */
	UPROPERTY(BlueprintReadWrite, Config, EditAnywhere, Category = "文本外观", meta=(DisplayName="阴影颜色与不透明度"))
	FLinearColor ShadowColorAndOpacity = FLinearColor::White;

	/** 文本相对于边距的对齐方式 */
	UPROPERTY(BlueprintReadWrite, Config, EditAnywhere, Category = "文本外观", meta=(DisplayName="对齐方式"))
	TEnumAsByte <ETextJustify::Type> Justification = ETextJustify::Left;
};

USTRUCT(BlueprintType)
struct FThrobberSettings
{
	GENERATED_BODY()

	/** 分段数量 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "外观", meta = (ClampMin = "1", ClampMax = "25", UIMin = "1", UIMax = "25", DisplayName="分段数量"))
	int32 NumberOfPieces = 3;

	/** 分段是否水平方向动画？ */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "外观", meta=(DisplayName="水平方向动画"))
	bool bAnimateHorizontally = true;

	/** 分段是否垂直方向动画？ */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "外观", meta=(DisplayName="垂直方向动画"))
	bool bAnimateVertically = true;

	/** 分段是否透明度动画？ */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "外观", meta=(DisplayName="透明度动画"))
	bool bAnimateOpacity = true;

	/** 进度条每一段使用的图片 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "外观", meta=(DisplayName="分段图片"))
	FSlateBrush Image;
};

USTRUCT(BlueprintType)
struct FCircularThrobberSettings
{
	GENERATED_BODY()

	/** 分段数量 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "外观", meta = (ClampMin = "1", ClampMax = "25", UIMin = "1", UIMax = "25", DisplayName="分段数量"))
	int32 NumberOfPieces = 6;

	/** 旋转一整圈所需时间（秒） */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "外观", meta = (ClampMin = "0", UIMin = "0", DisplayName="旋转周期（秒）"))
	float Period = 0.75f;

	/** 圆的半径。如果进度条是画布面板的子控件，需要先启用"适应内容大小"才能设置半径。 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "外观", meta=(DisplayName="半径"))
	float Radius = 64.0f;

	/** 进度条每一段使用的图片 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "外观", meta=(DisplayName="分段图片"))
	FSlateBrush Image;
};

USTRUCT(BlueprintType)
struct FImageSequenceSettings
{
	GENERATED_BODY()

	/** 用于加载图标动画的图片数组 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "加载控件设置", meta=(DisplayName="图片序列"))
	TArray<TObjectPtr<UTexture2D>> Images;

	/** 图片缩放比例 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "加载控件设置", meta=(DisplayName="缩放"))
	FVector2D Scale = FVector2D(1.0f, 1.0f);

	/**
	 * 更新图片的时间间隔（秒），值越小动画越快。设为0则每帧都更新图片。
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "加载控件设置", meta = (UIMax = 1.00, UIMin = 0.00, ClampMin = "0", ClampMax = "1", DisplayName="帧间隔（秒）"))
	float Interval = 0.05f;

	/** 是否倒序播放图片序列 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "加载控件设置", meta=(DisplayName="倒序播放"))
	bool bPlayReverse = false;
};

/**
 * 加载画面背景控件设置
 */
USTRUCT(BlueprintType)
struct ASYNCLOADINGSCREEN_API FBackgroundSettings
{
	GENERATED_BODY()

	// 加载画面中在视频上方随机显示的图片
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "背景", meta=(DisplayName="背景图片"))
	TArray<TObjectPtr<UTexture2D>> Images;

	// 随机切换背景图片的时间间隔（秒），小于等于0则不自动切换背景图片。
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "背景", meta=(DisplayName="自动切换间隔（秒）"))
	float UpdateInterval = 0.0f;

	// 图片的拉伸方式
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "背景", meta=(DisplayName="图片拉伸方式"))
	TEnumAsByte<EStretch::Type> ImageStretch = EStretch::ScaleToFit;

	/** 边框与所包含图片之间的内边距 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "背景", meta=(DisplayName="边距"))
	FMargin Padding;

	// 背景颜色。未定义图片时填满整个屏幕，否则在图片周围的边距区域可见（边距为0时隐藏）。
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "背景", meta=(DisplayName="背景颜色"))
	FLinearColor BackgroundColor = FLinearColor::Black;

	/**
	 * 如果为true，你需要在打开新关卡前在蓝图中调用"SetDisplayBackgroundIndex"函数
	 * 手动指定要在加载画面上显示的背景索引。如果索引无效，则随机显示"背景图片"数组中的图片。
	 * 指定有效索引后也会禁用随机"自动切换间隔"刷新，使选定的背景保持显示。
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "背景", meta=(DisplayName="手动指定背景索引"))
	bool bSetDisplayBackgroundManually = false;
};

/**
 * 加载控件设置
 */
USTRUCT(BlueprintType)
struct ASYNCLOADINGSCREEN_API FLoadingWidgetSettings
{
	GENERATED_BODY()

	FLoadingWidgetSettings();

	/** 加载图标类型 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "加载控件设置", meta=(DisplayName="加载图标类型"))
	ELoadingIconType LoadingIconType = ELoadingIconType::LIT_CircularThrobber;

	/** 加载控件布局方向 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "加载控件设置", meta=(DisplayName="加载控件布局"))
	ELoadingWidgetType LoadingWidgetType = ELoadingWidgetType::LWT_Horizontal;

	/** 加载图标的位移 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "加载控件设置", meta=(DisplayName="位移"))
	FVector2D TransformTranslation = FVector2D(0.0f, 0.0f);

	/** 加载图标的缩放，负值将翻转图标 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "加载控件设置", meta=(DisplayName="缩放"))
	FVector2D TransformScale = FVector2D(1.0f, 1.0f);

	/** 加载图标的轴心点（归一化局部空间） */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "加载控件设置", meta=(DisplayName="轴心点"))
	FVector2D TransformPivot = FVector2D(0.5f, 0.5f);

	// 显示在动画图标旁边的文本
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "加载控件设置", meta=(DisplayName="加载文本"))
	FText LoadingText;

	/** 加载文本是否在加载图标的右侧？仅当加载控件布局为"水平"时生效。 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "加载控件设置", meta=(DisplayName="文本在图标右侧"))
	bool bLoadingTextRightPosition = true;

	/** 加载文本是否在加载图标的上方？仅当加载控件布局为"垂直"时生效。 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "加载控件设置", meta=(DisplayName="文本在图标上方"))
	bool bLoadingTextTopPosition = true;

	// 加载文本外观设置
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "加载控件设置", meta=(DisplayName="文本外观"))
	FTextAppearance Appearance;

	/** 进度条设置。未选择"进度条"图标类型时忽略此项 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "加载控件设置", meta=(DisplayName="进度条设置"))
	FThrobberSettings ThrobberSettings;

	/** 圆形进度条设置。未选择"圆形进度条"图标类型时忽略此项 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "加载控件设置", meta=(DisplayName="圆形进度条设置"))
	FCircularThrobberSettings CircularThrobberSettings;

	/** 图片序列设置。未选择"图片序列"图标类型时忽略此项 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "加载控件设置", meta=(DisplayName="图片序列设置"))
	FImageSequenceSettings ImageSequenceSettings;

	/** 加载文本的对齐方式 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "加载控件设置", meta=(DisplayName="文本对齐"))
	FWidgetAlignment TextAlignment;

	/** 加载图标的对齐方式 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "加载控件设置", meta=(DisplayName="图标对齐"))
	FWidgetAlignment LoadingIconAlignment;

	/** 加载文本与加载图标之间的间距 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "加载控件设置", meta=(DisplayName="文本与图标间距"))
	float Space = 1.0f;

	/** 关卡加载完成后隐藏加载控件 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "加载控件设置", meta=(DisplayName="加载完成后隐藏控件"))
	bool bHideLoadingWidgetWhenCompletes = false;
};


/**
 * 提示文本设置
 */
USTRUCT(BlueprintType)
struct ASYNCLOADINGSCREEN_API FTipSettings
{
	GENERATED_BODY()

	// 在加载画面中随机显示的提示文本
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "提示设置", meta = (MultiLine = true, DisplayName="提示文本"))
	TArray<FText> TipText;

	// 随机切换提示文本的时间间隔（秒），小于等于0则不自动切换提示文本。
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "提示设置", meta=(DisplayName="自动切换间隔（秒）"))
	float UpdateInterval = 0.0f;

	// 提示文本外观设置
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "提示设置", meta=(DisplayName="文本外观"))
	FTextAppearance Appearance;

	// 提示文本换行前的宽度
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "提示设置", meta=(DisplayName="换行宽度"))
	float TipWrapAt = 0.0f;

	/**
	 * 如果为true，你需要在打开新关卡前在蓝图中调用"SetDisplayTipTextIndex"函数
	 * 手动指定要在加载画面上显示的提示文本索引。如果索引无效，则随机显示"提示文本"数组中的内容。
	 * 指定有效索引后也会禁用随机"自动切换间隔"刷新，使选定的提示保持显示。
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "提示设置", meta=(DisplayName="手动指定提示索引"))
	bool bSetDisplayTipTextManually = false;
};

/**
 * 加载完成时显示的文本。未设置"显示加载完成文本"=true时忽略此项
 */
USTRUCT(BlueprintType)
struct ASYNCLOADINGSCREEN_API FLoadingCompleteTextSettings
{
	GENERATED_BODY()

	// 关卡加载完成时显示的文本
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "加载完成文本设置", meta=(DisplayName="完成文本"))
	FText LoadingCompleteText;

	// 文本外观设置
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "加载完成文本设置", meta=(DisplayName="文本外观"))
	FTextAppearance Appearance;

	/** 文本对齐方式 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "加载完成文本设置", meta=(DisplayName="对齐"))
	FWidgetAlignment Alignment;

	/** 文本边距 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "加载完成文本设置", meta=(DisplayName="边距"))
	FMargin Padding;

	// 是否对文本进行动画？
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "加载完成文本设置", meta=(DisplayName="淡入淡出动画"))
	bool bFadeInOutAnim = true;

	/**
	 * 动画速度
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "加载完成文本设置", meta = (UIMax = 10.00, UIMin = 0.00, ClampMin = "0", ClampMax = "10", DisplayName="动画速度"))
	float AnimationSpeed = 1.0f;
};

/**
 * 显示PSO预编译着色器进度的进度条和文本。未设置"显示进度条控件"=true时忽略此项
 */
USTRUCT(BlueprintType)
struct ASYNCLOADINGSCREEN_API FPSOPrecacheProgressSettings
{
	GENERATED_BODY()

	FPSOPrecacheProgressSettings();

	/**
	 * 如果为true，显示带可选文本的进度条，展示PSO预编译着色器进度。
	 * 该控件仅在有待完成的PSO预编译时出现，编译完成后自动隐藏。
	 * 通常与"等待PSO预编译完成"一起使用。"显示控件覆盖层"=false时忽略此项。
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "PSO预编译进度设置", meta=(DisplayName="显示进度条控件"))
	bool bShowProgressWidget = false;

	/**
	 * 显示在进度条下方的文本。支持 {Percent} 和 {Remaining} 格式化参数，
	 * 例如 "正在编译着色器... {Percent}%" 或 "正在编译着色器（剩余 {Remaining}）"。留空则只显示进度条。
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "PSO预编译进度设置", meta=(DisplayName="进度文本"))
	FText ProgressText;

	// 进度文本外观设置
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "PSO预编译进度设置", meta=(DisplayName="文本外观"))
	FTextAppearance Appearance;

	/** 进度条样式（背景/填充画笔、填充颜色等） */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "PSO预编译进度设置", meta=(DisplayName="进度条样式"))
	FProgressBarStyle Style;

	/** 进度条尺寸 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "PSO预编译进度设置", meta=(DisplayName="进度条尺寸"))
	FVector2D BarSize = FVector2D(500.0f, 20.0f);

	/** 进度控件在屏幕上的对齐方式 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "PSO预编译进度设置", meta=(DisplayName="对齐方式"))
	FWidgetAlignment Alignment;

	/** 进度控件边距 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "PSO预编译进度设置", meta=(DisplayName="边距"))
	FMargin Padding = FMargin(0.0f, 0.0f, 0.0f, 60.0f);

	// 更新进度条和文本的时间间隔（秒）。设为0则每帧更新。
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "PSO预编译进度设置", meta = (UIMax = 1.00, UIMin = 0.00, ClampMin = "0", ClampMax = "1", DisplayName="更新间隔（秒）"))
	float UpdateInterval = 0.1f;
};

/**
 * 加载画面设置
 */
USTRUCT(BlueprintType)
struct ASYNCLOADINGSCREEN_API FALoadingScreenSettings
{
	GENERATED_BODY()

	// 加载画面的最短显示时间，-1表示无最短时间限制。建议设为-1。
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "视频设置", meta=(DisplayName="最短显示时间"))
	float MinimumLoadingScreenDisplayTime = -1;

	// 如果为true，加载完成后立即关闭加载画面。
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "视频设置", meta=(DisplayName="加载完成后自动关闭"))
	bool bAutoCompleteWhenLoadingCompletes = true;

	// 如果为true，加载完成后点击加载画面即可跳过视频。
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "视频设置", meta=(DisplayName="允许跳过视频"))
	bool bMoviesAreSkippable = true;

	/**
	 * 如果为true，视频将持续播放直到调用停止函数。
	 *
	 * 注意：如果将"最短显示时间"设为-1，玩家可以按任意键关闭加载画面。
	 * 如果"最短显示时间">=0，则必须在GameInstance、GameMode或PlayerController
	 * 蓝图的BeginPlay事件中调用"StopLoadingScreen"来关闭加载画面
	 * （此时"允许引擎Tick"必须设为true）
	 **/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "视频设置", meta=(DisplayName="等待手动关闭"))
	bool bWaitForManualStop = false;

	/** 如果为true，加载画面将不包含任何UObject或引擎功能，这将在支持的平台上更早地启动视频 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "视频设置", meta=(DisplayName="允许在启动早期显示"))
	bool bAllowInEarlyStartup = false;

	/** 如果为true，将在游戏线程等待加载视频结束期间调用引擎Tick。仅对启动后的加载画面有效，可能存在安全风险 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "视频设置", meta=(DisplayName="允许引擎Tick"))
	bool bAllowEngineTick = false;

	/**
	 * 如果为true，除了关卡加载外，加载画面还会保持显示直到所有未完成的PSO预编译
	 * （内置PSO缓存+运行时PSO预编译）全部完成。Epic推荐此选项，可避免玩家在加载画面关闭后
	 * 看到画面闪烁或卡顿。
	 *
	 * 注意：此设置会覆盖"等待手动关闭"选项：插件会强制将其设为true，并在PSO预编译完成后
	 * （或超过"PSO预编译最大等待时间"）且"最短显示时间"（如果>=0）已过后自动关闭加载画面，
	 * 因此无需手动调用"StopLoadingScreen"。如果"最短显示时间"=-1，即使PSO预编译仍在进行，
	 * 关卡加载完成后玩家仍可按任意键关闭加载画面。"允许在启动早期显示"=true时此项被忽略。
	 * PSO预编译被禁用时（r.PSOPrecaching=0，例如编辑器中或DirectX 11下）此项无效。
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "视频设置", meta=(DisplayName="等待PSO预编译完成"))
	bool bWaitForPSOPrecachingToComplete = false;

	/**
	 * "等待PSO预编译完成"的安全超时时间（秒），从关卡加载完成时开始计算。
	 * 如果超过此时间PSO预编译仍未完成，加载画面将照常关闭。设为0则无限等待。
	 * 建议设置大于0的值，尤其是项目还附带内置PSO缓存时，待处理计数可能长时间大于0。
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "视频设置", meta = (EditCondition = "bWaitForPSOPrecachingToComplete", UIMax = 60.00, UIMin = 0.00, ClampMin = "0", DisplayName="PSO预编译最大等待时间（秒）"))
	float PSOPrecacheMaxWaitTime = 0.0f;

	/**
	 * 如果为true，在加载画面显示期间将所有未完成的PSO预编译提升为最高优先级，使其更快完成。
	 * 加载画面关闭后恢复原优先级。PSO预编译被禁用时（r.PSOPrecaching=0）此项无效。
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "视频设置", meta = (EditCondition = "bWaitForPSOPrecachingToComplete", DisplayName="提升PSO预编译优先级"))
	bool bBoostPSOPrecachePriority = true;

	/** 播放模式：播放、循环等。注意：如果播放模式为MT_LoopLast，播放完最后一个视频时将自动开启"加载完成后自动关闭" */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "视频设置", meta=(DisplayName="播放模式"))
	TEnumAsByte<EMoviePlaybackType> PlaybackType = EMoviePlaybackType::MT_Normal;

	/**
	 * 所有视频文件必须放在 Content/Movies/ 目录下。推荐格式：MPEG-4 (mp4)。
	 * 输入时不要带文件扩展名。
	 * 例如：如果 Content/Movies/ 文件夹下有 my_movie.mp4，则在此输入 my_movie。
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "视频设置", meta=(DisplayName="视频文件路径"))
	TArray<FString> MoviePaths;

	/**
	 * 如果为true，播放前随机打乱视频列表顺序。
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "视频设置", meta=(DisplayName="随机播放"))
	bool bShuffle = false;

	/**
	 * 如果为true，将忽略"随机播放"选项，你需要在打开新关卡前在蓝图中调用
	 * "SetDisplayMovieIndex"函数手动指定要播放的视频索引。
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "视频设置", meta=(DisplayName="手动指定视频索引"))
	bool bSetDisplayMovieIndexManually = false;


	/**
	 * 是否显示加载画面控件（背景/提示/加载控件）？如果只想播放视频，建议设为false。
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "加载画面设置", meta=(DisplayName="显示控件覆盖层"))
	bool bShowWidgetOverlay = true;

	/**
	 * 如果为true，关卡加载完成时显示一段文本。"显示控件覆盖层"=false时忽略此项。
	 *
	 * 注意：要正确启用此选项，需要将"等待手动关闭"设为true，且"最短显示时间"设为-1。
	 * 同时允许玩家按任意键关闭加载画面。
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "加载画面设置", meta=(DisplayName="显示加载完成文本"))
	bool bShowLoadingCompleteText = false;

	/**
	 * 加载完成时显示的文本设置。"显示加载完成文本"=false时忽略此项。
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "加载画面设置", meta=(DisplayName="加载完成文本设置"))
	FLoadingCompleteTextSettings LoadingCompleteTextSettings;

	/** 加载画面的背景控件。"显示控件覆盖层"=false时忽略此项 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "加载画面设置", meta=(DisplayName="背景设置"))
	FBackgroundSettings Background;

	/** 加载画面的提示控件。"显示控件覆盖层"=false时忽略此项 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "加载画面设置", meta=(DisplayName="提示设置"))
	FTipSettings TipWidget;

	/** 加载画面的加载控件。"显示控件覆盖层"=false时忽略此项 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "加载画面设置", meta=(DisplayName="加载控件设置"))
	FLoadingWidgetSettings LoadingWidget;

	/** 加载画面的PSO预编译进度控件。"显示控件覆盖层"=false时忽略此项 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "加载画面设置", meta=(DisplayName="PSO预编译进度控件"))
	FPSOPrecacheProgressSettings PSOPrecacheProgressWidget;

	/**
	 * 选择异步加载画面的布局。"显示控件覆盖层"=false时忽略此项
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "加载画面设置", meta=(DisplayName="布局选择"))
	EAsyncLoadingScreenLayout Layout = EAsyncLoadingScreenLayout::ALSL_Classic;
};

/** 经典布局设置 */
USTRUCT(BlueprintType)
struct FClassicLayoutSettings
{
	GENERATED_BODY()

	/** 包含加载和提示控件的边框是位于底部还是顶部？ */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "经典布局", meta=(DisplayName="控件在底部"))
	bool bIsWidgetAtBottom = true;

	/** 加载控件是否在提示文本的左侧？ */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "经典布局", meta=(DisplayName="加载控件在左侧"))
	bool bIsLoadingWidgetAtLeft = true;

	/** 加载控件与提示文本之间的间距 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "经典布局", meta=(DisplayName="控件间距"))
	float Space = 1.0f;

	/** 提示文本的对齐方式 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "经典布局", meta=(DisplayName="提示对齐"))
	FWidgetAlignment TipAlignment;

	/** 边框背景的水平对齐方式 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "居中布局", meta=(DisplayName="边框水平对齐"))
	TEnumAsByte<EHorizontalAlignment> BorderHorizontalAlignment = EHorizontalAlignment::HAlign_Fill;

	/** 边框与所包含控件之间的内边距 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "经典布局", meta=(DisplayName="边框边距"))
	FMargin BorderPadding;

	/** 边框控件的背景外观设置 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "经典布局", meta=(DisplayName="边框背景"))
	FSlateBrush BorderBackground;
};

/** 居中布局设置 */
USTRUCT(BlueprintType)
struct FCenterLayoutSettings
{
	GENERATED_BODY()

	/** 提示文本位于底部还是顶部？ */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "居中布局", meta=(DisplayName="提示在底部"))
	bool bIsTipAtBottom = true;

	/** 提示文本的对齐方式 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "居中布局", meta=(DisplayName="提示对齐"))
	FWidgetAlignment TipAlignment;

	/** 边框的水平对齐方式 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "居中布局", meta=(DisplayName="边框水平对齐"))
	TEnumAsByte<EHorizontalAlignment> BorderHorizontalAlignment = EHorizontalAlignment::HAlign_Fill;

	/** 根据提示文本位于底部或顶部，向屏幕底部或顶部的偏移量 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "居中布局", meta=(DisplayName="边框垂直偏移"))
	float BorderVerticalOffset = 0.0f;

	/** 边框与所包含提示文本之间的内边距 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "居中布局", meta=(DisplayName="边框边距"))
	FMargin BorderPadding;

	/** 提示区域的背景外观设置 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "居中布局", meta=(DisplayName="边框背景"))
	FSlateBrush BorderBackground;
};

/** 信箱模式布局设置 */
USTRUCT(BlueprintType)
struct FLetterboxLayoutSettings
{
	GENERATED_BODY()

	/** 加载控件位于底部还是顶部？ */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "信箱模式布局", meta=(DisplayName="加载控件在顶部"))
	bool bIsLoadingWidgetAtTop = true;

	/** 提示文本的对齐方式 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "信箱模式布局", meta=(DisplayName="提示对齐"))
	FWidgetAlignment TipAlignment;

	/** 加载控件的对齐方式 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "信箱模式布局", meta=(DisplayName="加载控件对齐"))
	FWidgetAlignment LoadingWidgetAlignment;

	/** 上边框的水平对齐方式 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "信箱模式布局", meta=(DisplayName="上边框水平对齐"))
	TEnumAsByte<EHorizontalAlignment> TopBorderHorizontalAlignment = EHorizontalAlignment::HAlign_Fill;

	/** 下边框的水平对齐方式 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "信箱模式布局", meta=(DisplayName="下边框水平对齐"))
	TEnumAsByte<EHorizontalAlignment> BottomBorderHorizontalAlignment = EHorizontalAlignment::HAlign_Fill;

	/** 上边框与所包含控件之间的内边距 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "信箱模式布局", meta=(DisplayName="上边框边距"))
	FMargin TopBorderPadding;

	/** 下边框与所包含控件之间的内边距 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "信箱模式布局", meta=(DisplayName="下边框边距"))
	FMargin BottomBorderPadding;

	/** 上边框的背景外观设置 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "信箱模式布局", meta=(DisplayName="上边框背景"))
	FSlateBrush TopBorderBackground;

	/** 下边框的背景外观设置 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "信箱模式布局", meta=(DisplayName="下边框背景"))
	FSlateBrush BottomBorderBackground;
};

/** 侧边栏布局设置 */
USTRUCT(BlueprintType)
struct FSidebarLayoutSettings
{
	GENERATED_BODY()

	/** 包含加载和提示控件的边框位于右侧还是左侧？ */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "侧边栏布局", meta=(DisplayName="控件在右侧"))
	bool bIsWidgetAtRight = true;

	/** 加载控件是否在提示文本的上方？ */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "侧边栏布局", meta=(DisplayName="加载控件在上方"))
	bool bIsLoadingWidgetAtTop = true;

	/** 加载控件与提示文本之间的间距 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "侧边栏布局", meta=(DisplayName="控件间距"))
	float Space = 1.0f;

	/** 包含加载/提示控件的垂直框的垂直对齐方式 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "侧边栏布局", meta=(DisplayName="垂直对齐"))
	TEnumAsByte<EVerticalAlignment> VerticalAlignment = EVerticalAlignment::VAlign_Center;

	/** 加载控件的对齐方式 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "侧边栏布局", meta=(DisplayName="加载控件对齐"))
	FWidgetAlignment LoadingWidgetAlignment;

	/** 提示文本的对齐方式 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "侧边栏布局", meta=(DisplayName="提示对齐"))
	FWidgetAlignment TipAlignment;

	/** 包含所有控件的边框背景的垂直对齐方式 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "侧边栏布局", meta=(DisplayName="边框垂直对齐"))
	TEnumAsByte<EVerticalAlignment> BorderVerticalAlignment = EVerticalAlignment::VAlign_Fill;

	/** 根据边框位于左侧或右侧，向屏幕左侧或右侧的偏移量 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "侧边栏布局", meta=(DisplayName="边框水平偏移"))
	float BorderHorizontalOffset = 0.0f;

	/** 边框与所包含控件之间的内边距 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "侧边栏布局", meta=(DisplayName="边框边距"))
	FMargin BorderPadding;

	/** 边框控件的背景外观设置 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "侧边栏布局", meta=(DisplayName="边框背景"))
	FSlateBrush BorderBackground;
};

/** 双侧边栏布局设置 */
USTRUCT(BlueprintType)
struct FDualSidebarLayoutSettings
{
	GENERATED_BODY()

	/** 加载控件位于右边框还是左边框？ */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "双侧边栏布局", meta=(DisplayName="加载控件在右侧"))
	bool bIsLoadingWidgetAtRight = true;

	/** 左侧控件的垂直对齐方式 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "双侧边栏布局", meta=(DisplayName="左侧垂直对齐"))
	TEnumAsByte<EVerticalAlignment> LeftVerticalAlignment = EVerticalAlignment::VAlign_Center;

	/** 右侧控件的垂直对齐方式 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "双侧边栏布局", meta=(DisplayName="右侧垂直对齐"))
	TEnumAsByte<EVerticalAlignment> RightVerticalAlignment = EVerticalAlignment::VAlign_Center;

	/** 左边框背景的垂直对齐方式 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "双侧边栏布局", meta=(DisplayName="左边框垂直对齐"))
	TEnumAsByte<EVerticalAlignment> LeftBorderVerticalAlignment = EVerticalAlignment::VAlign_Fill;

	/** 右边框背景的垂直对齐方式 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "双侧边栏布局", meta=(DisplayName="右边框垂直对齐"))
	TEnumAsByte<EVerticalAlignment> RightBorderVerticalAlignment = EVerticalAlignment::VAlign_Fill;

	/** 左边框与所包含控件之间的内边距 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "双侧边栏布局", meta=(DisplayName="左边框边距"))
	FMargin LeftBorderPadding;

	/** 右边框与所包含控件之间的内边距 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "双侧边栏布局", meta=(DisplayName="右边框边距"))
	FMargin RightBorderPadding;

	/** 左边框控件的背景外观设置 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "双侧边栏布局", meta=(DisplayName="左边框背景"))
	FSlateBrush LeftBorderBackground;

	/** 右边框控件的背景外观设置 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "双侧边栏布局", meta=(DisplayName="右边框背景"))
	FSlateBrush RightBorderBackground;
};

/**
 * 异步加载画面设置
 */
UCLASS(Config = "Game", defaultconfig, meta = (DisplayName = "异步加载画面"))
class ASYNCLOADINGSCREEN_API ULoadingScreenSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:

	ULoadingScreenSettings(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	/**
	 * 首次打开游戏时的启动加载画面。可在此设置工作室Logo视频。
	 */
	UPROPERTY(Config, EditAnywhere, Category = "常规", meta=(DisplayName="启动加载画面"))
	FALoadingScreenSettings StartupLoadingScreen;

	/**
	 * 打开新关卡时的默认加载画面。
	 */
	UPROPERTY(Config, EditAnywhere, Category = "常规", meta=(DisplayName="默认加载画面"))
	FALoadingScreenSettings DefaultLoadingScreen;

	/**
	 * 经典布局设置。
	 * 经典布局是一种简单通用的布局，适配多种设计风格。
	 * 包含加载和提示控件的边框可以位于屏幕底部或顶部。
	 */
	UPROPERTY(Config, EditAnywhere, Category = "布局", meta=(DisplayName="经典布局设置"))
	FClassicLayoutSettings Classic;

	/**
	 * 居中布局设置。
	 * 加载控件位于屏幕中央，提示控件可以在底部或顶部。
	 * 如果加载图标是主要视觉元素，居中布局是不错的选择。
	 */
	UPROPERTY(Config, EditAnywhere, Category = "布局", meta=(DisplayName="居中布局设置"))
	FCenterLayoutSettings Center;

	/**
	 * 信箱模式布局设置。
	 * 信箱模式在屏幕上下各有一条边框。加载控件可以在上边，
	 * 提示文本在下边，反之亦然。
	 */
	UPROPERTY(Config, EditAnywhere, Category = "布局", meta=(DisplayName="信箱模式布局设置"))
	FLetterboxLayoutSettings Letterbox;

	/**
	 * 侧边栏布局设置。
	 * 侧边栏布局在屏幕左侧或右侧有一条垂直边框。
	 * 由于提示控件较高，侧边栏适合用于故事叙述、长文本展示。
	 */
	UPROPERTY(Config, EditAnywhere, Category = "布局", meta=(DisplayName="侧边栏布局设置"))
	FSidebarLayoutSettings Sidebar;

	/**
	 * 双侧边栏布局设置。
	 * 与侧边栏类似，但双侧边栏在屏幕左右两侧各有一条垂直边框。
	 * 双侧边栏适合用于故事叙述、长文本展示。
	 */
	UPROPERTY(Config, EditAnywhere, Category = "布局", meta=(DisplayName="双侧边栏布局设置"))
	FDualSidebarLayoutSettings DualSidebar;

};
