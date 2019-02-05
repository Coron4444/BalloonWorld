//================================================================================
//!	@file	 Interpolation.h
//!	@brief	 補間Class
//! @details Template
//!	@author  Kai Araki									@date 2018/02/04
//================================================================================
#ifndef	_INTERPOLATION_H_
#define _INTERPOLATION_H_



//****************************************
// インクルード文
//****************************************
#include "SafeRelease.h"



//************************************************************														   
//! @brief   補間要素Class(Template)
//!
//! @details 補間用のClass(Template)
//************************************************************
template<class Value, class Distance = double, class AddInfo = double>
class InterpolationElement
{
//====================
// 変数
//====================
private:
	Value value_;			//!< キー値
	Distance distance_;		//!< 補間距離(前の要素からの相対距離)
	AddInfo add_info_;		//!< 付加情報


//====================
// プロパティ
//====================
public:
	//----------------------------------------
	//! @brief キー値取得関数
	//! @details
	//! @param void なし
	//! @retval Value* キー値
	//----------------------------------------
	Value* getpValue()
	{
		return &value_;
	}

	//----------------------------------------
	//! @brief 補間距離取得関数
	//! @details
	//! @param void なし
	//! @retval Distance* 補間距離
	//----------------------------------------
	Distance* getpDistance()
	{
		return &distance_;
	}

	//----------------------------------------
	//! @brief 付加情報取得関数
	//! @details
	//! @param void なし
	//! @retval AddInfo* 付加情報
	//----------------------------------------
	AddInfo* getpAddInfo()
	{
		return &add_info_;
	}


//====================
// 関数
//====================
public:
	//----------------------------------------
	//! @brief コンストラクタ
	//! @details
	//! @param &value    キー値
	//! @param &distance 補間距離
	//! @param &add_info 付加情報
	//----------------------------------------
	InterpolationElement(Value& value, Distance& distance, AddInfo& add_info)
		: value_(value),
		distance_(distance),
		add_info_(add_info)
	{
	}
};



//************************************************************														   
//! @brief   補間ストラテジBaseClass(Template)
//!
//! @details 補間ストラテジのBaseClass(Template)
//************************************************************
template<class Value, class Distance = double, class AddInfo = double>
class InterpolationStrategyBase
{
//====================
// 型定義
//====================
public:
	typedef typename InterpolationElement<Value, Distance, AddInfo> Element;


//====================
// プロパティ
//====================
public:
	//----------------------------------------
	//! @brief 必要な要素の数取得関数
	//! @details
	//! @param void なし
	//! @retval size_t 必要な要素の数
	//----------------------------------------
	virtual size_t getNeedElementNum() = 0;

	//----------------------------------------
	//! @brief 要素を登録する配列取得関数
	//! @details
	//! @param void なし
	//! @retval Element** 要素を登録する配列
	//----------------------------------------
	virtual Element** getp2Array() = 0;


//====================
// 関数
//====================
public:
	//----------------------------------------
	//! @brief 補間値算出関数
	//! @details
	//! @param *value    キー値
	//! @param &distance 補間距離
	//! @retval bool 補間成功の有無
	//----------------------------------------
	virtual bool CalculationOfInterpolation(Value* value,
											Distance& distance) = 0;
};



//************************************************************														   
//! @brief   線形補完ストラテジClass(Template)
//!
//! @details 線形補完ストラテジのClass(Template)
//************************************************************
template<class Value, class Distance = double, class AddInfo = double>
class LinerInterpolationStrategy : public InterpolationStrategyBase<Value, Distance, AddInfo>
{
//====================
// 型定義
//====================
public:
	typedef typename InterpolationElement<Value, Distance, AddInfo> Element;

//====================
// 変数
//====================
private:
	Element* element_[2] = {nullptr};		// 要素数

//====================
// プロパティ
//====================
public:
	//----------------------------------------
	//! @brief 必要な要素の数取得関数
	//! @details
	//! @param void なし
	//! @retval size_t 必要な要素の数
	//----------------------------------------
	size_t getNeedElementNum()
	{
		return 2;
	}

	//----------------------------------------
	//! @brief 要素を登録する配列取得関数
	//! @details
	//! @param void なし
	//! @retval Element** 要素を登録する配列
	//----------------------------------------
	Element** getp2Array()
	{
		return (Element**)&element_;
	}


//====================
// 関数
//====================
public:
	//----------------------------------------
	//! @brief 補間値算出関数
	//! @details
	//! @param *value    キー値
	//! @param &distance 補間距離
	//! @retval bool 補間成功の有無
	//----------------------------------------
	bool CalculationOfInterpolation(Value* value,
									Distance& distance)
	{
		// 線形補間計算
		*value = (Value)((1 - distance) * *element_[0]->getpValue()
			+ *element_[1]->getpValue() * distance);
		return true;
	}
};



//************************************************************														   
//! @brief   補間Class(Template)
//!
//! @details 補間要素のコンテナClass(Template)
//! @details このコンテナで扱いたいValueには、
//! @details 各InterpolationStrategyで使用する、
//! @details 演算子のオーバーライドが必要です。
//************************************************************
template<class Value, class Distance = double, class AddInfo = double, class Strategy = LinerInterpolationStrategy<Value, Distance, AddInfo>>
class Interpolation
{
//====================
// 型定義
//====================
public:
	typedef typename InterpolationElement<Value, Distance, AddInfo> Element;


//====================
// 定数
//====================
private:
#define END_POINTER ((Element*)(-1))


//====================
// クラス
//====================
public:
	//****************************************											   
	//! @brief   補間コンテナイテレータClass
	//!
	//! @details 補間コンテナのイテレータClass
	//****************************************
	class Iterator_
	{
	//====================
	// 変数
	//====================
	private:
		Element** first_pointer_;			//!< イテレータの最初のポインタ
		Interpolation* interpolation_;		//!< 補間クラス
		Value current_value_;				//!< 現在の補間値
		Distance distance_unit_;			//!< 単位距離
		Distance current_distance_;			//!< 現在の距離
		Distance cumulative_distance_;		//!< 累積の距離
		size_t offset_index_;				//!< オフセットインデックス値
		size_t max_index_;					//!< 最大インデックス値
		size_t target_index_;				//!< 目標要素のインデックス
		Element* target_element_;			//!< 目標の要素
		bool is_finished_;					//!< 終端フラグ
		Strategy strategy_;					//!< 補間計算


	//====================
	// プロパティ
	//====================
	public:
		//----------------------------------------
		//! @brief 現在の補間値取得関数
		//! @details
		//! @param void なし
		//! @retval Value& 現在の補間値
		//----------------------------------------
		Value& getValue()
		{
			return current_value_;
		}

		//----------------------------------------
		//! @brief 単位距離設定関数
		//! @details
		//! @param value 単位距離
		//! @retval void なし
		//----------------------------------------
		void setDistanceUnit(Distance& value)
		{
			distance_unit_ = value;
		}

		//----------------------------------------
		//! @brief 累積の距離取得関数
		//! @details
		//! @param void なし
		//! @retval Distance 累積の距離
		//----------------------------------------
		Distance getCumulativeDistance()
		{
			return cumulative_distance_;
		}

		//----------------------------------------
		//! @brief 終端フラグ取得関数
		//! @details
		//! @param void なし
		//! @retval bool 終端フラグ
		//----------------------------------------
		bool getIsFinished()
		{
			return is_finished_;
		}

	//====================
	// 演算子
	//====================
	public:
		//----------------------------------------
		//! @brief *間接指定演算子関数
		//! @details
		//! @param void なし
		//! @retval Value& 現在の補間値
		//----------------------------------------
		Value& operator *()
		{
			return current_value_;
		}

		//----------------------------------------
		//! @brief ++増加単項演算子関数
		//! @details
		//! @param dummy ダミー
		//! @retval void なし
		//----------------------------------------
		void operator ++(int dummy)
		{
			dummy = dummy;
			next(distance_unit_);	// 単位距離分更新
		}

		//----------------------------------------
		//! @brief ==比較演算子関数
		//! @details
		//! @param iterator イテレータ
		//! @retval void なし
		//----------------------------------------
		bool operator ==(Iterator_ iterator)
		{
			if (iterator.target_element_ == target_element_) return true;
			return false;
		}

		//----------------------------------------
		//! @brief !=比較演算子関数
		//! @details
		//! @param iterator イテレータ
		//! @retval void なし
		//----------------------------------------
		bool operator !=(Iterator_ iterator)
		{
			if (iterator.target_element_ != target_element_) return true;
			return false;
		}


	//====================
	// 関数
	//====================
	public:
		//----------------------------------------
		//! @brief コンストラクタ
		//! @details
		//! @param **element_array 要素配列
		//! @param *interpolation  補間クラス
		//----------------------------------------
		Iterator_(Element** element_array = nullptr, 
				  Interpolation* interpolation = nullptr)
			:first_pointer_(element_array),
			interpolation_(interpolation),
			distance_unit_(1),
			current_distance_(0),
			cumulative_distance_(0),
			offset_index_(0),
			max_index_(0),
			target_index_(0),
			target_element_(END_POINTER),
			is_finished_(true)
		{
			if (element_array == nullptr) return;

			// 先頭からのオフセットインデックス
			offset_index_ = ((size_t)element_array - (size_t)interpolation
							 ->getp2FirstPointer()) / sizeof(Element*);

			// 最大インデックス数
			max_index_ = interpolation->size() - offset_index_;

			// 現在の補間値の初期値
			current_value_ = *element_array[0]->getpValue();

			// 要素が２個以上なら補間可能
			if (max_index_ < 2) return;

			// 目標要素を設定
			target_index_ = 1;
			target_element_ = first_pointer_[target_index_];

			// 終端フラグOFF
			is_finished_ = false;
		}

	private:
		//----------------------------------------
		//! @brief イテレータ更新関数
		//! @details
		//! @param &distance 補間距離
		//! @retval Iterator_ 更新後のイテレータ
		//----------------------------------------
		Iterator_ next(Distance& distance)
		{
			// 現在の区間の何割に進んだかを算出
			Distance ratio = CalculationDistance(distance);

			// 補間計算に必要な要素数を取得
			size_t need_element_num = strategy_.getNeedElementNum();

			// 補間計算用配列の取得
			Element** temp_element_array = strategy_.getp2Array();

			// 補間計算用配列に要素を代入
			if (!SubstitutionElement(need_element_num, temp_element_array))
			{
				// 終端フラグがONなら終端イテレータを返す
				if (is_finished_ || (*first_pointer_ == END_POINTER))
				{
					// 目標要素を終端ポインタに変更
					target_element_ = END_POINTER;
					return *this;
				}
				else
				{
					// 最後の要素に合わせる
					is_finished_ = true;
					target_element_ = first_pointer_[interpolation_->size() - 1];
					current_value_ = *target_element_->getpValue();
					return *this;
				}
			}

			// 次の値に更新(補間計算)
			strategy_.CalculationOfInterpolation(&current_value_, ratio);
			return *this;
		}

		//----------------------------------------
		//! @brief 補間距離算出関数
		//! @details
		//! @param &distance 補間距離
		//! @retval Distance 補間距離
		//----------------------------------------
		Distance CalculationDistance(Distance& distance)
		{
			// 終端ポインタ及び要素数が１つの時
			if (*first_pointer_ == END_POINTER) return 1;
			if (interpolation_->size() <= 1) return 1;

			// 距離を加算
			current_distance_ += distance;
			cumulative_distance_ += distance;	// 累積にも追加

			// 現在の目標要素を確定
			for (; ;)
			{
				// 目標要素が存在するか確認
				if (target_index_ >= max_index_) return 1;

				// 現在の距離が目標要素区間幅を超えていないか確認
				if (current_distance_
					>= *first_pointer_[offset_index_ + target_index_]->getpDistance())
				{
					// 飛び出た距離を算出し目標要素インデックスを次に変更する
					current_distance_ -= *first_pointer_[offset_index_ + target_index_]->getpDistance();
					target_index_++;
					continue;
				}
				break;
			}
			target_element_ = first_pointer_[offset_index_ + target_index_];

			// 目標要素に対する補間距離の算出(0~1)
			return current_distance_ / *target_element_->getpDistance();
		}

		//----------------------------------------
		//! @brief 補間計算用配列に要素を代入関数
		//! @details
		//! @param need_element_num 補間に必要な要素数
		//! @param element_array    要素を代入する配列
		//! @retval bool 要素格納の成功の有無
		//----------------------------------------
		bool SubstitutionElement(size_t need_element_num, Element** element_array)
		{
			// 目標要素より1つ前の要素を起点とし最後の要素インデックスを算出
			size_t last_element_num = (target_index_ - 1) + need_element_num;
			if (last_element_num > max_index_) return false;

			// 配列に代入コピー
			memcpy(element_array, first_pointer_ + target_index_ - 1, 
				   need_element_num * sizeof(Element*));
			return true;
		}
	};


//====================
// 型定義
//====================
public:
	typedef typename Interpolation<Value, Distance>::Iterator_ Iterator;


//====================
// 変数
//====================
private:
	size_t size_;				//!< 配列数
	Element** element_;			//!< 要素配列
	Element** end_pointer_;		//!< 終端ポインタ


//====================
// プロパティ
//====================
public:
	//----------------------------------------
	//! @brief 最初のポインタ取得取得関数
	//! @details
	//! @param void なし
	//! @retval Vector3D* 前ベクトル
	//----------------------------------------
	Element** getp2FirstPointer()
	{
		return element_;
	}


//====================
// 関数
//====================
public:
	//----------------------------------------
	//! @brief コンストラクタ
	//! @details
	//! @param void なし
	//----------------------------------------
	Interpolation()
	{
		size_ = 0;
		element_ = (Element**)malloc(sizeof(Element*));
		*element_ = END_POINTER;
		end_pointer_ = element_;
	}

	//----------------------------------------
	//! @brief デストラクタ
	//! @details
	//! @param void なし
	//----------------------------------------
	~Interpolation()
	{
		clear();
		free(element_);
	}

	//----------------------------------------
	//! @brief 追加関数
	//! @details
	//! @param &value    キー値
	//! @param &distance 補間距離
	//! @param add_info 付加情報
	//! @retval void なし
	//----------------------------------------
	void push_back(Value& value, Distance& distance, AddInfo add_info = 1.0)
	{
		// 要素生成
		Element* temp_element = new Element(value, distance, add_info);
		AddArrayMemory(1);
		Rewrite(temp_element);

	}

	//----------------------------------------
	//! @brief クリア関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void clear()
	{
		// 解放
		for (size_t i = 0; i < size_; i++)
		{
			delete element_[i];
		}
		size_ = 0;
		element_ = (Element**)realloc(element_, sizeof(Element*));
		*element_ = END_POINTER;
		end_pointer_ = element_;
	}

	//----------------------------------------
	//! @brief 始まりイテレータ関数
	//! @details
	//! @param void なし
	//! @retval Iterator 始まりイテレータ
	//----------------------------------------
	Iterator begin()
	{
		// 要素生成
		return Iterator(element_, this);
	}

	//----------------------------------------
	//! @brief 終端イテレーター関数
	//! @details
	//! @param void なし
	//! @retval Iterator 終端イテレータ
	//----------------------------------------
	Iterator end()
	{
		// 要素生成
		return Iterator(nullptr, this);
	}

	//----------------------------------------
	//! @brief サイズ関数
	//! @details
	//! @param void なし
	//! @retval size_t サイズ
	//----------------------------------------
	size_t size()
	{
		return size_;
	}

private:
	//----------------------------------------
	//! @brief 配列メモリー追加関数
	//! @details
	//! @param add_num 追加数 
	//! @retval void なし
	//----------------------------------------
	void AddArrayMemory(size_t add_num)
	{
		if (add_num <= 0) return;

		// 配列リサイズ
		element_ = (Element**)realloc(element_, sizeof(Element*) * (size_ + add_num));

		// リサイズ分初期化
		for (size_t i = 0; i < add_num; i++)
		{
			element_[size_ + i] = END_POINTER;
		}

		// サイズ数及び終端ポインタ更新
		size_ += add_num;
		end_pointer_ = element_ + size_ - 1;
	}

	//----------------------------------------
	//! @brief 配列上書き関数
	//! @details
	//! @param new_element 新規配列
	//! @retval void なし
	//----------------------------------------
	void Rewrite(Element* new_element)
	{
		// 上書き部分のポインタ先を解放
		if (*end_pointer_ != END_POINTER)
		{
			delete *end_pointer_;
		}

		*end_pointer_ = new_element;
	}
};



#endif