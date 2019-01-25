//================================================================================
//
//    �L�[�{�[�h���̓w�b�_
//    Author : Araki Kai                                �쐬�� : 2017/07/25
//
//================================================================================

#ifndef _KYEBOARD_H_
#define _KYEBOARD_H_



//**********************************************************************
//
// �C���N���[�h��
//
//**********************************************************************

#include < Windows.h >
#define DIRECTINPUT_VERSION		( 0x0800 )
#include < dinput.h >



//**********************************************************************
//
// �v���g�^�C�v�錾
//
//**********************************************************************

//================================================================================
//
// [ �L�[�{�[�h�̏������֐� ]
//
// � ���� �
//
// �hInstance : �C���X�^���X�n���h��
// �hWnd : �E�B���h�E�n���h��
//
// � �߂�l �
//
// �HRESULT�^ : �G���[�`�F�b�N�p
//
//�y �ڍ� �z
//
// ��L�[�{�[�h���g�p����Ƃ��̏�����
//
//================================================================================

HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd);



//================================================================================
//
// [ �L�[�{�[�h�̏I�������֐� ]
//
// � ���� �
//
// ��Ȃ�
//
// � �߂�l �
//
// ��Ȃ�
//
//�y �ڍ� �z
//
// ��L�[�{�[�h�̎g�p���I������Ƃ��̏���
//
//================================================================================

void UninitKeyboard(void);



//================================================================================
//
// [ �L�[�{�[�h�̍X�V�֐� ]
//
// � ���� �
//
// ��Ȃ�
//
// � �߂�l �
//
// ��Ȃ�
//
//�y �ڍ� �z
//
// ��L�[�{�[�h�̍X�V
//
//================================================================================

void UpdateKeyboard(void);



//================================================================================
//
// [ �L�[�{�[�h�̃v���X��Ԃ��擾����֐� ]
//
// � ���� �
//
// �nkey : �v���X��Ԃ��m�F�������L�[�{�[�h�̃{�^��ID
//
// � �߂�l �
//
// �bool : �v���X����Ă邩�t���O��Ԃ�
//
//�y �ڍ� �z
//
// ��n���ꂽ�L�[�{�[�h�{�^����������Ă��邩�𔻒f����
// �������Ă���Ƃ���true�A������Ă��Ȃ��Ƃ���false��Ԃ�
//
//================================================================================

bool GetKeyboardPress(int nKey);



//================================================================================
//
// [ �L�[�{�[�h�̃g���K�[��Ԃ��擾����֐� ]
//
// � ���� �
//
// �nkey : �g���K�[��Ԃ��m�F�������L�[�{�[�h�̃{�^��ID
//
// � �߂�l �
//
// �bool : �g���K�[����Ă邩�t���O��Ԃ�
//
//�y �ڍ� �z
//
// ��n���ꂽ�L�[�{�[�h�{�^���������ꂽ�u�Ԃ��ǂ����𔻒f����
// ��������u�Ԃ�true�A����ȊO��false��Ԃ�
//
//================================================================================

bool GetKeyboardTrigger(int nKey);



//================================================================================
//
// [ �L�[�{�[�h�̃��s�[�g��Ԃ��擾����֐� ]
//
// � ���� �
//
// �nkey : ���s�[�g��Ԃ��m�F�������L�[�{�[�h�̃{�^��ID
//
// � �߂�l �
//
// �bool : ���s�[�g����Ă邩�t���O��Ԃ�
//
//�y �ڍ� �z
//
// ��n���ꂽ�L�[�{�[�h�{�^����������Ă����莞�Ԃ��̂܂܂��𔻒f����
// �������Ă����莞�Ԃ��̂܂܂̂Ƃ�true�A�������u�Ԃ�false��Ԃ�
//
//================================================================================

bool GetKeyboardRepeat(int nKey);



//================================================================================
//
// [ �L�[�{�[�h�̃����|�X��Ԃ��擾����֐� ]
//
// � ���� �
//
// �nkey : �����|�X��Ԃ��m�F�������L�[�{�[�h�̃{�^��ID
//
// � �߂�l �
//
// �bool : �����|�X����Ă邩�t���O��Ԃ�
//
//�y �ڍ� �z
//
// ��n���ꂽ�L�[�{�[�h�{�^���������ꂽ�u�Ԃ��ǂ����𔻒f����
// ��������u�Ԃ�true�A����ȊO��false��Ԃ�
//
//================================================================================

bool GetKeyboardRelease(int nKey);



#endif