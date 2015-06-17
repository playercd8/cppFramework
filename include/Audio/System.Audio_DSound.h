/*
* System.Audio_DSound.h
*
* Code Status: Drafts
*  Created on: Taiwan
*      Author: player
*/

#include "../stdafx.h"
#if (_AUDIO_MODE == _AUDIO_MODE_DSOUND)
#include <dsound.h>
#pragma comment(lib, "dsound.lib")

#include "../System.Buffer.h"
#include "../System.ComPtr.h"

#ifndef SYSTEM_AUDIO_SOUND_DEVICE_H_
#define SYSTEM_AUDIO_SOUND_DEVICE_H_

#if _MSC_VER > 1000
#pragma once
#endif

namespace System {
	namespace Audio {
		class SoundDevice;
		class Sound;
		class StreamingSound;
		class WaveFile;

		class SoundDevice : public ComPtr<IDirectSound8>
		{
		public:
			SoundDevice();
			~SoundDevice();

			HRESULT Initialize(HWND hWnd, DWORD dwCoopLevel);
			//inline  LPDIRECTSOUND8 GetDirectSound() { return m_pDS; }
			HRESULT SetPrimaryBufferFormat(DWORD dwPrimaryChannels, DWORD dwPrimaryFreq, DWORD dwPrimaryBitRate);
			HRESULT Get3DListenerInterface(LPDIRECTSOUND3DLISTENER* ppDSListener);

			HRESULT Create(Sound** ppSound, LPTSTR strWaveFileName, DWORD dwCreationFlags = 0, GUID guid3DAlgorithm = GUID_NULL, DWORD dwNumBuffers = 1);
			HRESULT CreateFromMemory(Sound** ppSound, BYTE* pbData, ULONG ulDataSize, LPWAVEFORMATEX pwfx, DWORD dwCreationFlags = 0, GUID guid3DAlgorithm = GUID_NULL, DWORD dwNumBuffers = 1);
			HRESULT CreateStreaming(StreamingSound** ppStreamingSound, LPTSTR strWaveFileName, DWORD dwCreationFlags, GUID guid3DAlgorithm, DWORD dwNotifyCount, DWORD dwNotifySize, HANDLE hNotifyEvent);
		};

		// Encapsulates functionality of a DirectSound buffer.
		class Sound
		{
		protected:
			LPDIRECTSOUNDBUFFER*	m_apDSBuffer;
			DWORD					m_dwDSBufferSize;
			WaveFile*				m_pWaveFile;
			DWORD					m_dwNumBuffers;
			DWORD					m_dwCreationFlags;

			HRESULT RestoreBuffer(LPDIRECTSOUNDBUFFER pDSB, BOOL* pbWasRestored);

		public:
			Sound(LPDIRECTSOUNDBUFFER* apDSBuffer, DWORD dwDSBufferSize, DWORD dwNumBuffers, WaveFile* pWaveFile, DWORD dwCreationFlags);
			virtual ~Sound();

			HRESULT Get3DBufferInterface(DWORD dwIndex, LPDIRECTSOUND3DBUFFER* ppDS3DBuffer);
			HRESULT FillBufferWithSound(LPDIRECTSOUNDBUFFER pDSB, BOOL bRepeatWavIfBufferLarger);
			LPDIRECTSOUNDBUFFER GetFreeBuffer();
			LPDIRECTSOUNDBUFFER GetBuffer(DWORD dwIndex);

			HRESULT Play(DWORD dwPriority = 0, DWORD dwFlags = 0, LONG lVolume = 0, LONG lFrequency = -1, LONG lPan = 0);
			HRESULT Play3D(LPDS3DBUFFER p3DBuffer, DWORD dwPriority = 0, DWORD dwFlags = 0, LONG lFrequency = 0);
			HRESULT Stop();
			HRESULT Reset();
			BOOL    IsSoundPlaying();
		};

		// Encapsulates functionality to play a wave file with DirectSound.
		//       The Create() method loads a chunk of wave file into the buffer,
		//       and as sound plays more is written to the buffer by calling
		//       HandleWaveStreamNotification() whenever hNotifyEvent is signaled.
		class StreamingSound : public Sound
		{
		protected:
			DWORD m_dwLastPlayPos;
			DWORD m_dwPlayProgress;
			DWORD m_dwNotifySize;
			DWORD m_dwNextWriteOffset;
			BOOL  m_bFillNextNotificationWithSilence;

		public:
			StreamingSound(LPDIRECTSOUNDBUFFER pDSBuffer, DWORD dwDSBufferSize, WaveFile* pWaveFile, DWORD dwNotifySize);
			~StreamingSound();

			HRESULT HandleWaveStreamNotification(BOOL bLoopedPlay);
			HRESULT Reset();
		};

		// Encapsulates reading or writing sound data to or from a wave file
		class WaveFile
		{
		public:
			WAVEFORMATEX* m_pwfx;        // Pointer to WAVEFORMATEX structure
			HMMIO         m_hmmio;       // MM I/O handle for the WAVE
			MMCKINFO      m_ck;          // Multimedia RIFF chunk
			MMCKINFO      m_ckRiff;      // Use in opening a WAVE file
			DWORD         m_dwSize;      // The size of the wave file
			MMIOINFO      m_mmioinfoOut;
			DWORD         m_dwFlags;
			BOOL          m_bIsReadingFromMemory;
			LPBYTE        m_pbData;
			LPBYTE        m_pbDataCur;
			ULONG         m_ulDataSize;
			CHAR*         m_pResourceBuffer;

		protected:
			HRESULT ReadMMIO();
			HRESULT WriteMMIO(WAVEFORMATEX *pwfxDest);

		public:
			WaveFile();
			~WaveFile();

			HRESULT Open(LPTSTR strFileName, WAVEFORMATEX* pwfx, DWORD dwFlags);
			HRESULT OpenFromMemory(BYTE* pbData, ULONG ulDataSize, WAVEFORMATEX* pwfx, DWORD dwFlags);
			HRESULT Close();

			HRESULT Read(BYTE* pBuffer, DWORD dwSizeToRead, DWORD* pdwSizeRead);
			HRESULT Write(UINT nSizeToWrite, BYTE* pbData, UINT* pnSizeWrote);

			DWORD   GetSize();
			HRESULT ResetFile();
			WAVEFORMATEX* GetFormat() { return m_pwfx; };
		};
	} /* namespace Audio */
} /* namespace System */

#endif /*  SYSTEM_AUDIO_SOUND_DEVICE_H_ */
#endif