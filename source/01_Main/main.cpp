//================================================================================
//!	@file	 main.cpp
//!	@brief	 ���C��
//! @details 
//!	@author  Kai Araki									@date 2017/09/01
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include <windows.h>
#include <crtdbg.h>
#include <assert.h>

#include "main.h"

#include <SafeRelease/SafeRelease.h>
#include <GameSystem\GameSystem.h>



//****************************************
// �萔��`
//****************************************
static const char* CLASS_NAME = "DirectXProject";
static const char* WINDOW_NAME = "DirectX�Q�[��";
static const DWORD WINDOW_STYLE = WS_OVERLAPPEDWINDOW & ~(WS_THICKFRAME | WS_MAXIMIZEBOX);



//****************************************
// �v���g�^�C�v�錾
//****************************************
HWND Create_Window(HINSTANCE hInstance, int nCmdShow);
void RegistrationWindowClassEx(HINSTANCE hInstance);
void SetClientAreaSize(int* window_width, int* window_height);
void SetWindowPositionCenter(int* window_position_x, int* window_position_y,
							 int* window_width, int* window_height);
void MessageAndGameLoop(HINSTANCE hInstance, HWND window_handle, MSG* message);
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

// ImGUI�}�E�X����
//#ifdef _DEBUG
extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
//#endif



//--------------------------------------------------
// -�A�v���P�[�V�����̃G���g���[�֐�
//--------------------------------------------------
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevinstance, LPSTR lpCmdLine, int nCmdShow)
{
	// �g���Ă��Ȃ������̏���
	lpCmdLine = lpCmdLine;
	hPrevinstance = hPrevinstance;

	// ���������[�N���o
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF | _CRTDBG_CHECK_ALWAYS_DF);
	//_CrtSetBreakAlloc(11526);


	// �E�B���h�E�̍쐬
	HWND window_handle = Create_Window(hInstance, nCmdShow);

	// ���b�Z�[�W&�Q�[�����[�v
	MSG message;
	MessageAndGameLoop(hInstance, window_handle, &message);

	return (int)message.wParam;
}



//--------------------------------------------------
// -�E�B���h�E�̍쐬�֐�
//--------------------------------------------------
HWND Create_Window(HINSTANCE hInstance, int nCmdShow)
{
	// �E�B���h�E�p�f�[�^
	int window_position_x = 0;
	int window_position_y = 0;
	int window_width = 0;
	int window_height = 0;

	// �E�B���h�E�N���XEx�̓o�^
	RegistrationWindowClassEx(hInstance);

	// �N���C�A���g�̈�̃T�C�Y�ݒ�
	SetClientAreaSize(&window_width, &window_height);

	// �E�B���h�E�̏ꏊ�𒆉��ɕύX
	SetWindowPositionCenter(&window_position_x, &window_position_y,
							&window_width, &window_height);

	// �E�B���h�E�̍쐬(�o�^����Ă���E�B���h�E�N���X����ՂƂ���)
	HWND window_handle = CreateWindowEx(0,					// �g���E�B���h�E�X�^�C��
										CLASS_NAME,			// �E�B���h�E�̖��O
										WINDOW_NAME,		// �E�B���h�E�㕔�ɕ\������閼�O
										WINDOW_STYLE,		// �E�B���h�E�X�^�C��
										window_position_x,	// �E�B���h�E�̂w���W
										window_position_y,	// �E�B���h�E�̂x���W
										window_width, 		// �E�B���h�E�̕�
										window_height,		// �E�B���h�E�̍���
										NULL,				// �e�E�B���h�E�̃n���h��
										NULL,				// ���j���[�̗L��
										hInstance,			// �C���X�^���X�n���h��
										NULL);				// ���b�Z�[�W�ɓn�����p�����[�^

	// �E�B���h�E��\����Ԃɂ���
	ShowWindow(window_handle, nCmdShow);

	// �E�B���h�E�̃N���C�A���g�̈���X�V����
	UpdateWindow(window_handle);

	return window_handle;
}



//--------------------------------------------------
// -WindowClassEx�̓o�^�֐�(Window�̔ėp�I�͐ݒ�)
//--------------------------------------------------
void RegistrationWindowClassEx(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);					// �\���̂̃T�C�Y
	wcex.style = CS_VREDRAW | CS_HREDRAW;				// �E�B���h�E�X�^�C��
	wcex.lpfnWndProc = WndProc;							// ���̃E�B���h�E�̃��b�Z�[�W���󂯎��R�[���o�b�N�֐��ւ̃|�C���^
	wcex.cbClsExtra = 0;								// �E�B���h�E�N���X�\���̂̌��Ɋ��蓖�Ă�⑫�o�C�g��
	wcex.cbWndExtra = 0;								// �E�B���h�E�C���X�^���X�̌��Ɋ��蓖�Ă�⑫�o�C�g��
	wcex.hInstance = hInstance;							// ���̃E�B���h�E�ׂ̈̃E�B���h�E�v���V�[�W���̂���C���X�^���X�n���h��
	wcex.hIcon = NULL;									// �A�C�R���̃n���h��
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);			// �}�E�X�J�[�\���̃n���h��
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);	// �E�B���h�E�w�i�F(�w�i�`��p�u���V�̃n���h��)
	wcex.lpszMenuName = NULL;							// �f�t�H���g���j���[��
	wcex.lpszClassName = CLASS_NAME;					// �E�B���h�E�̖��O
	wcex.hIconSm = NULL;								// 16�~16�̏������T�C�Y�̃A�C�R��


	// WNDCLASSEX�^��wcex�̒��g��o�^
	RegisterClassEx(&wcex);
}



//--------------------------------------------------
// -�N���C�A���g�̈�̃T�C�Y�ݒ�֐�
//--------------------------------------------------
void SetClientAreaSize(int* window_width, int* window_height)
{
	// �N���C�A���g�̈�̍��W��������`�f�[�^
	RECT wr = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};

	// �w�肵���N���C�A���g�̈�̃T�C�Y+���j���[�o�[�Ȃǂ̗̈�̃T�C�Y�����v������`�f�[�^���Z�o
	AdjustWindowRect(&wr,			// �N���C�A���g�̈�̍��W��������`�f�[�^ 
					 WINDOW_STYLE,	// �E�B���h�E�X�^�C��
					 FALSE);		// ���j���[�̗L��

	// �Z�o���ꂽ��`����E�B���h�E�T�C�Y���Z�o
	*window_width = wr.right - wr.left;
	*window_height = wr.bottom - wr.top;
}



//--------------------------------------------------
// -�E�B���h�E���W�𒆉��ɐݒ�֐�
//--------------------------------------------------
void SetWindowPositionCenter(int* window_position_x, int* window_position_y,
							 int* window_width, int* window_height)
{
	// �f�X�N�g�b�v�T�C�Y(�f�X�N�g�b�v�̋�`�f�[�^)�̎擾
	RECT desktop_rect;
	GetWindowRect(GetDesktopWindow(), &desktop_rect);

	// �E�B���h�E�𒆉��ɂ���Ƃ��̃E�B���h�E�̍��W���Z�o
	*window_position_x = (desktop_rect.right - *window_width) / 2;
	*window_position_y = (desktop_rect.bottom - *window_height) / 2;

	// �E�B���h�E���W����ʂ��傫�����ǂ���
	if ((desktop_rect.right - desktop_rect.left) < *window_position_x)
	{
		*window_position_x = 0;
	}
	if ((desktop_rect.bottom - desktop_rect.top) < *window_position_y)
	{
		*window_position_y = 0;
	}
}



//--------------------------------------------------
// -���b�Z�[�W&�Q�[�����[�v�֐�
//--------------------------------------------------
void MessageAndGameLoop(HINSTANCE hInstance, HWND window_handle, MSG* message)
{
	// �Q�[���V�X�e���̍쐬
	GameSystem* game_system = new GameSystem();

	// �Q�[���V�X�e���̏�����
	bool is_init = game_system->Init(hInstance, window_handle, TRUE, SCREEN_WIDTH, SCREEN_HEIGHT);
	assert(is_init && "�������Ɏ��s���܂���!!(main.cpp)");

	// �^�C�}�[�p�ϐ�
	DWORD time = timeGetTime();
	DWORD old_time = timeGetTime();

	// �^�C�}�[�̐��\���グ��
	timeBeginPeriod(1);

	for (; ;)
	{
		// ���b�Z�[�W����
		if (PeekMessage(message, NULL, 0, 0, PM_REMOVE))
		{
			// �I�����b�Z�[�W�������甲����
			if (message->message == WM_QUIT)
			{
				break;
			}
			else
			{
				TranslateMessage(message);
				DispatchMessage(message);
			}
		}
		else
		{// �Q�[������

			// ���݂̎��Ԃ�ۑ�
			time = timeGetTime();

			// 1000ms / 60���Ƃɏ���(60FPS)
			if ((time - old_time) >= (1000 / 60))
			{
				// �Q�[���V�X�e���̍X�V
				game_system->Update();

				// �Q�[���V�X�e���̕`��
				game_system->Draw();

				// ��X�V
				game_system->LateUpdate();

				// �O��̎����̍X�V
				old_time = time;
			}
		}
	}

	// �Q�[���V�X�e���̏I������
	game_system->Uninit();
	SafeRelease::Normal(&game_system);

	// �^�C�}�[�̐��\��߂�
	timeEndPeriod(1);
}



//--------------------------------------------------
// -�E�B���h�E�v���V�[�W���֐�
//--------------------------------------------------
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{

//#ifdef _DEBUG
	// ImGUI�}�E�X����
	if (ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam)) return true;
//#endif

	switch (uMsg)
	{
		case WM_DESTROY:
		{// �E�B���h�E�j�����b�Z�[�W

			PostQuitMessage(0);
			break;
		}
		case WM_KEYDOWN:
		{// �L�[�{�[�h����

			switch (wParam)
			{
				case VK_ESCAPE:
				{// Esc�L�[

					int nID = MessageBox(hWnd, "�I�����܂����H", "�I�����b�Z�[�W", MB_YESNO | MB_DEFBUTTON2);

					if (nID == IDYES)
					{
						DestroyWindow(hWnd);
					}
					break;
				}
			}
			break;
		}
		case WM_CLOSE:
		{// �~�{�^��

			int nID = MessageBox(hWnd, "�I�����܂����H", "�I�����b�Z�[�W", MB_YESNO | MB_DEFBUTTON2);

			if (nID == IDYES)
			{
				DestroyWindow(hWnd);
			}
			else
			{
				return 0;
			}
			break;
		}
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}