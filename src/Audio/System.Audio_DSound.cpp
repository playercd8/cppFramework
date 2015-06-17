/*
* System.IO.File_CPP11.cpp
*
* Code Status: Drafts
*  Created on: Taiwan
*      Author: player
*/
#include "../../include/stdafx.h"
#if (_AUDIO_MODE == _AUDIO_MODE_DSOUND)

#include "../../include/System.AutoPtr.h"
#include "../../include/System.ComPtr.h"
#include "../../include/Audio/System.Audio_DSound.h"

#include <mmsystem.h>
#pragma comment(lib, "Winmm.lib")

#if (_DRAWING_MODE == _DRAWING_MODE_DX11)
#include "../../include/DX11/DX11.h"
#elif (_DRAWING_MODE == _DRAWING_MODE_DX10)
#include "../../include/DX10/DX10.h"
#elif (_DRAWING_MODE == _DRAWING_MODE_DX9)
#include "../../include/DX9/DX9.h"
#endif

namespace System {
	namespace Audio {
#define WAVEFILE_READ   1
#define WAVEFILE_WRITE  2

		//---------------------------------------------------------------------------------------------------------
		// class SoundDevice
#pragma region class SoundDevice

		// Constructs
		SoundDevice::SoundDevice()
		{
		}

		// Destroys the class
		SoundDevice::~SoundDevice()
		{
		}

		// Initializes the IDirectSound object and also sets the primary buffer format.
		// This function must be called before any others.
		HRESULT SoundDevice::Initialize(HWND hWnd, DWORD dwCoopLevel)
		{
			HRESULT             hr;

			SafeRelease(_ptr);

			// Create IDirectSound using the primary sound device
			V(DirectSoundCreate8(NULL, &_ptr, NULL));
			if (FAILED(hr))
				return hr;

			// Set DirectSound coop level
			V(_ptr->SetCooperativeLevel(hWnd, dwCoopLevel));
			if (FAILED(hr))
				return hr;

			return S_OK;
		}

		//-----------------------------------------------------------------------------
		// Desc: Set primary buffer to a specified format
		//       !WARNING! - Setting the primary buffer format and then using this
		//                   same dsound object for DirectMusic messes up DirectMusic!
		//       For example, to set the primary buffer format to 22kHz stereo, 16-bit
		//       then:   dwPrimaryChannels = 2
		//               dwPrimaryFreq     = 22050,
		//               dwPrimaryBitRate  = 16
		//-----------------------------------------------------------------------------
		HRESULT SoundDevice::SetPrimaryBufferFormat(DWORD dwPrimaryChannels,
			DWORD dwPrimaryFreq,
			DWORD dwPrimaryBitRate)
		{
			HRESULT             hr;
			LPDIRECTSOUNDBUFFER pDSBPrimary = NULL;

			if (_ptr == NULL)
				return CO_E_NOTINITIALIZED;

			// Get the primary buffer
			DSBUFFERDESC dsbd;
			ZeroMemory(&dsbd, sizeof(DSBUFFERDESC));
			dsbd.dwSize = sizeof(DSBUFFERDESC);
			dsbd.dwFlags = DSBCAPS_PRIMARYBUFFER;
			dsbd.dwBufferBytes = 0;
			dsbd.lpwfxFormat = NULL;

			V(_ptr->CreateSoundBuffer(&dsbd, &pDSBPrimary, NULL));
			if (FAILED(hr))
				return hr;

			WAVEFORMATEX wfx;
			ZeroMemory(&wfx, sizeof(WAVEFORMATEX));
			wfx.wFormatTag = (WORD)WAVE_FORMAT_PCM;
			wfx.nChannels = (WORD)dwPrimaryChannels;
			wfx.nSamplesPerSec = (DWORD)dwPrimaryFreq;
			wfx.wBitsPerSample = (WORD)dwPrimaryBitRate;
			wfx.nBlockAlign = (WORD)(wfx.wBitsPerSample / 8 * wfx.nChannels);
			wfx.nAvgBytesPerSec = (DWORD)(wfx.nSamplesPerSec * wfx.nBlockAlign);

			V(pDSBPrimary->SetFormat(&wfx));

			// Release the primary buffer, since it is not need anymore
			SafeRelease(pDSBPrimary);

			if (FAILED(hr))
				return hr;

			return S_OK;
		}

		//-----------------------------------------------------------------------------
		// Desc: Returns the 3D listener interface associated with primary buffer.
		//-----------------------------------------------------------------------------
		HRESULT SoundDevice::Get3DListenerInterface(LPDIRECTSOUND3DLISTENER* ppDSListener)
		{
			HRESULT             hr;
			DSBUFFERDESC        dsbdesc;
			LPDIRECTSOUNDBUFFER pDSBPrimary = NULL;

			if (ppDSListener == NULL)
				return E_INVALIDARG;
			if (_ptr == NULL)
				return CO_E_NOTINITIALIZED;

			*ppDSListener = NULL;

			// Obtain primary buffer, asking it for 3D control
			ZeroMemory(&dsbdesc, sizeof(DSBUFFERDESC));
			dsbdesc.dwSize = sizeof(DSBUFFERDESC);
			dsbdesc.dwFlags = DSBCAPS_CTRL3D | DSBCAPS_PRIMARYBUFFER;
			V(_ptr->CreateSoundBuffer(&dsbdesc, &pDSBPrimary, NULL));
			if (FAILED(hr))
				return hr;

			V(pDSBPrimary->QueryInterface(IID_IDirectSound3DListener, (VOID**)ppDSListener));

			// Release the primary buffer, since it is not need anymore
			SafeRelease(pDSBPrimary);

			if (FAILED(hr))
				return hr;

			return S_OK;
		}

		HRESULT SoundDevice::Create(Sound** ppSound,
			LPTSTR strWaveFileName,
			DWORD dwCreationFlags,
			GUID guid3DAlgorithm,
			DWORD dwNumBuffers)
		{
			HRESULT hr;
			HRESULT hrRet = S_OK;
			DWORD   i;
			LPDIRECTSOUNDBUFFER* apDSBuffer = NULL;
			DWORD                dwDSBufferSize = NULL;
			WaveFile*            pWaveFile = NULL;

			if (_ptr == NULL)
				return CO_E_NOTINITIALIZED;
			if (strWaveFileName == NULL || ppSound == NULL || dwNumBuffers < 1)
				return E_INVALIDARG;

			try {
				apDSBuffer = new LPDIRECTSOUNDBUFFER[dwNumBuffers];
				if (apDSBuffer == NULL)	{
					hr = E_OUTOFMEMORY;
					throw hr;
				}

				pWaveFile = new WaveFile();
				if (pWaveFile == NULL) {
					hr = E_OUTOFMEMORY;
					throw hr;
				}

				V(pWaveFile->Open(strWaveFileName, NULL, WAVEFILE_READ));

				if (pWaveFile->GetSize() == 0) {
					// Wave is blank, so don't create it.
					hr = E_FAIL;
					throw hr;
				}

				// Make the DirectSound buffer the same size as the wav file
				dwDSBufferSize = pWaveFile->GetSize();

				// Create the direct sound buffer, and only request the flags needed
				// since each requires some overhead and limits if the buffer can
				// be hardware accelerated
				DSBUFFERDESC dsbd;
				ZeroMemory(&dsbd, sizeof(DSBUFFERDESC));
				dsbd.dwSize = sizeof(DSBUFFERDESC);
				dsbd.dwFlags = dwCreationFlags;
				dsbd.dwBufferBytes = dwDSBufferSize;
				dsbd.guid3DAlgorithm = guid3DAlgorithm;
				dsbd.lpwfxFormat = pWaveFile->m_pwfx;

				// DirectSound is only guarenteed to play PCM data.  Other
				// formats may or may not work depending the sound card driver.
				V(_ptr->CreateSoundBuffer(&dsbd, &apDSBuffer[0], NULL));

				// Be sure to return this error code if it occurs so the
				// callers knows this happened.
				if (hr == DS_NO_VIRTUALIZATION)
					hrRet = DS_NO_VIRTUALIZATION;

				if (FAILED(hr))
					throw hr;

				// Default to use DuplicateSoundBuffer() when created extra buffers since always
				// create a buffer that uses the same memory however DuplicateSoundBuffer() will fail if
				// DSBCAPS_CTRLFX is used, so use CreateSoundBuffer() instead in this case.
				if ((dwCreationFlags & DSBCAPS_CTRLFX) == 0) {
					for (i = 1; i < dwNumBuffers; i++) {
						V(_ptr->DuplicateSoundBuffer(apDSBuffer[0], &apDSBuffer[i]));
						if (FAILED(hr))
							throw hr;
					}
				}
				else {
					for (i = 1; i < dwNumBuffers; i++) {
						V(_ptr->CreateSoundBuffer(&dsbd, &apDSBuffer[i], NULL));
						if (FAILED(hr))
							throw hr;
					}
				}

				// Create the sound
				*ppSound = new Sound(apDSBuffer, dwDSBufferSize, dwNumBuffers, pWaveFile, dwCreationFlags);

				SafeDeleteArray(apDSBuffer);
				return hrRet;
			}
			catch (...) {
				// Cleanup
				SafeDelete(pWaveFile);
				SafeDeleteArray(apDSBuffer);
				return hr;
			}
		}

		HRESULT SoundDevice::CreateFromMemory(Sound** ppSound,
			LPBYTE pbData,
			ULONG  ulDataSize,
			LPWAVEFORMATEX pwfx,
			DWORD dwCreationFlags,
			GUID guid3DAlgorithm,
			DWORD dwNumBuffers)
		{
			HRESULT hr;
			DWORD   i;
			LPDIRECTSOUNDBUFFER* apDSBuffer = NULL;
			DWORD                dwDSBufferSize = NULL;
			WaveFile*            pWaveFile = NULL;

			if (_ptr == NULL)
				return CO_E_NOTINITIALIZED;
			if (pbData == NULL || ppSound == NULL || dwNumBuffers < 1)
				return E_INVALIDARG;

			try {
				apDSBuffer = new LPDIRECTSOUNDBUFFER[dwNumBuffers];
				if (apDSBuffer == NULL)	{
					hr = E_OUTOFMEMORY;
					throw hr;
				}

				pWaveFile = new WaveFile();
				if (pWaveFile == NULL) {
					hr = E_OUTOFMEMORY;
					throw hr;
				}

				pWaveFile->OpenFromMemory(pbData, ulDataSize, pwfx, WAVEFILE_READ);

				// Make the DirectSound buffer the same size as the wav file
				dwDSBufferSize = ulDataSize;

				// Create the direct sound buffer, and only request the flags needed
				// since each requires some overhead and limits if the buffer can
				// be hardware accelerated
				DSBUFFERDESC dsbd;
				ZeroMemory(&dsbd, sizeof(DSBUFFERDESC));
				dsbd.dwSize = sizeof(DSBUFFERDESC);
				dsbd.dwFlags = dwCreationFlags;
				dsbd.dwBufferBytes = dwDSBufferSize;
				dsbd.guid3DAlgorithm = guid3DAlgorithm;
				dsbd.lpwfxFormat = pwfx;

				V(_ptr->CreateSoundBuffer(&dsbd, &apDSBuffer[0], NULL));
				if (FAILED(hr))
					throw hr;

				// Default to use DuplicateSoundBuffer() when created extra buffers since always
				// create a buffer that uses the same memory however DuplicateSoundBuffer() will fail if
				// DSBCAPS_CTRLFX is used, so use CreateSoundBuffer() instead in this case.
				if ((dwCreationFlags & DSBCAPS_CTRLFX) == 0) {
					for (i = 1; i < dwNumBuffers; i++) {
						V(_ptr->DuplicateSoundBuffer(apDSBuffer[0], &apDSBuffer[i]));
						if (FAILED(hr))
							throw hr;
					}
				}
				else {
					for (i = 1; i < dwNumBuffers; i++) {
						V(_ptr->CreateSoundBuffer(&dsbd, &apDSBuffer[i], NULL));
						if (FAILED(hr))
							throw hr;
					}
				}

				// Create the sound
				*ppSound = new Sound(apDSBuffer, dwDSBufferSize, dwNumBuffers, pWaveFile, dwCreationFlags);

				SafeDeleteArray(apDSBuffer);
				return S_OK;
			}
			catch (...) {
				// Cleanup
				SafeDelete(pWaveFile);
				SafeDeleteArray(apDSBuffer);
				return hr;
			}
		}

		//-----------------------------------------------------------------------------
		// Name: CSoundManager::CreateStreaming()
		// Desc:
		//-----------------------------------------------------------------------------
		HRESULT SoundDevice::CreateStreaming(StreamingSound** ppStreamingSound,
			LPTSTR strWaveFileName,
			DWORD dwCreationFlags,
			GUID guid3DAlgorithm,
			DWORD dwNotifyCount,
			DWORD dwNotifySize,
			HANDLE hNotifyEvent)
		{
			HRESULT hr;

			if (_ptr == NULL)
				return CO_E_NOTINITIALIZED;
			if (strWaveFileName == NULL || ppStreamingSound == NULL || hNotifyEvent == NULL)
				return E_INVALIDARG;

			LPDIRECTSOUNDBUFFER pDSBuffer = NULL;
			DWORD               dwDSBufferSize = NULL;
			WaveFile*           pWaveFile = NULL;
			DSBPOSITIONNOTIFY*  aPosNotify = NULL;
			LPDIRECTSOUNDNOTIFY pDSNotify = NULL;

			try {
				pWaveFile = new WaveFile();
				if (pWaveFile == NULL) {
					hr = E_OUTOFMEMORY;
					throw hr;
				}
				pWaveFile->Open(strWaveFileName, NULL, WAVEFILE_READ);

				// Figure out how big the DSound buffer should be
				dwDSBufferSize = dwNotifySize * dwNotifyCount;

				// Set up the direct sound buffer.  Request the NOTIFY flag, so
				// that we are notified as the sound buffer plays.  Note, that using this flag
				// may limit the amount of hardware acceleration that can occur.
				DSBUFFERDESC dsbd;
				ZeroMemory(&dsbd, sizeof(DSBUFFERDESC));
				dsbd.dwSize = sizeof(DSBUFFERDESC);
				dsbd.dwFlags = dwCreationFlags |
					DSBCAPS_CTRLPOSITIONNOTIFY |
					DSBCAPS_GETCURRENTPOSITION2;
				dsbd.dwBufferBytes = dwDSBufferSize;
				dsbd.guid3DAlgorithm = guid3DAlgorithm;
				dsbd.lpwfxFormat = pWaveFile->m_pwfx;

				V(_ptr->CreateSoundBuffer(&dsbd, &pDSBuffer, NULL));
				if (FAILED(hr))
					throw hr;

				// Create the notification events, so that we know when to fill
				// the buffer as the sound plays.
				V(pDSBuffer->QueryInterface(IID_IDirectSoundNotify, (VOID**)&pDSNotify));
				if (FAILED(hr))
					throw hr;

				aPosNotify = new DSBPOSITIONNOTIFY[dwNotifyCount];
				if (aPosNotify == NULL) {
					hr = E_OUTOFMEMORY;
					throw hr;
				}

				for (DWORD i = 0; i < dwNotifyCount; i++) {
					aPosNotify[i].dwOffset = (dwNotifySize * i) + dwNotifySize - 1;
					aPosNotify[i].hEventNotify = hNotifyEvent;
				}

				// Tell DirectSound when to notify us. The notification will come in the from
				// of signaled events that are handled in WinMain()
				V(pDSNotify->SetNotificationPositions(dwNotifyCount, aPosNotify));
				if (FAILED(hr))
					throw hr;

				SafeRelease(pDSNotify);
				SafeDeleteArray(aPosNotify);

				// Create the sound
				*ppStreamingSound = new StreamingSound(pDSBuffer, dwDSBufferSize, pWaveFile, dwNotifySize);

				return S_OK;
			}
			catch (...) {
				SafeDelete(pWaveFile);
				SafeRelease(pDSNotify);
				SafeDeleteArray(aPosNotify);
				return hr;
			}
		}

#pragma endregion class SoundDevice

		//---------------------------------------------------------------------------------------------------------
		// class Sound
#pragma region class Sound

		// Constructs the class
		Sound::Sound(LPDIRECTSOUNDBUFFER* apDSBuffer, DWORD dwDSBufferSize,
			DWORD dwNumBuffers, WaveFile* pWaveFile, DWORD dwCreationFlags)
		{
			DWORD i;

			m_apDSBuffer = new LPDIRECTSOUNDBUFFER[dwNumBuffers];
			if (NULL != m_apDSBuffer) {
				for (i = 0; i < dwNumBuffers; i++)
					m_apDSBuffer[i] = apDSBuffer[i];

				m_dwDSBufferSize = dwDSBufferSize;
				m_dwNumBuffers = dwNumBuffers;
				m_pWaveFile = pWaveFile;
				m_dwCreationFlags = dwCreationFlags;

				FillBufferWithSound(m_apDSBuffer[0], FALSE);
			}
		}

		// Destroys
		Sound::~Sound()
		{
			for (DWORD i = 0; i < m_dwNumBuffers; i++)
				SafeRelease(m_apDSBuffer[i]);

			SafeDeleteArray(m_apDSBuffer);
			SafeDelete(m_pWaveFile);
		}

		// Fills a DirectSound buffer with a sound file
		HRESULT Sound::FillBufferWithSound(LPDIRECTSOUNDBUFFER pDSB, BOOL bRepeatWavIfBufferLarger)
		{
			HRESULT hr;
			void*   pDSLockedBuffer = NULL; // Pointer to locked buffer memory
			DWORD   dwDSLockedBufferSize = 0;    // Size of the locked DirectSound buffer
			DWORD   dwWavDataRead = 0;    // Amount of data read from the wav file

			if (pDSB == NULL)
				return CO_E_NOTINITIALIZED;

			// Make sure we have focus, and we didn't just switch in from
			// an app which had a DirectSound device
			V(RestoreBuffer(pDSB, NULL));
			if (FAILED(hr))
				return hr;

			// Lock the buffer down
			V(pDSB->Lock(0, m_dwDSBufferSize, &pDSLockedBuffer, &dwDSLockedBufferSize, NULL, NULL, 0L));
			if (FAILED(hr))
				return hr;

			// Reset the wave file to the beginning
			m_pWaveFile->ResetFile();

			V(m_pWaveFile->Read((LPBYTE)pDSLockedBuffer, dwDSLockedBufferSize, &dwWavDataRead));
			if (FAILED(hr))
				return hr;

			if (dwWavDataRead == 0) {
				// Wav is blank, so just fill with silence
				FillMemory(pDSLockedBuffer,
					dwDSLockedBufferSize,
					(BYTE)(m_pWaveFile->m_pwfx->wBitsPerSample == 8 ? 128 : 0));
			} else if (dwWavDataRead < dwDSLockedBufferSize) {
				// If the wav file was smaller than the DirectSound buffer,
				// we need to fill the remainder of the buffer with data
				if (bRepeatWavIfBufferLarger) {
					// Reset the file and fill the buffer with wav data
					DWORD dwReadSoFar = dwWavDataRead;    // From previous call above.
					while (dwReadSoFar < dwDSLockedBufferSize) {
						// This will keep reading in until the buffer is full
						// for very short files
						V(m_pWaveFile->ResetFile());
						if (FAILED(hr))
							return hr;

						V(m_pWaveFile->Read((LPBYTE)pDSLockedBuffer + dwReadSoFar,
							dwDSLockedBufferSize - dwReadSoFar,
							&dwWavDataRead));
						if (FAILED(hr))
							return hr;

						dwReadSoFar += dwWavDataRead;
					}
				} else {
					// Don't repeat the wav file, just fill in silence
					FillMemory((LPBYTE)pDSLockedBuffer + dwWavDataRead,
						dwDSLockedBufferSize - dwWavDataRead,
						(BYTE)(m_pWaveFile->m_pwfx->wBitsPerSample == 8 ? 128 : 0));
				}
			}

			// Unlock the buffer, we don't need it anymore.
			pDSB->Unlock(pDSLockedBuffer, dwDSLockedBufferSize, NULL, 0);

			return S_OK;
		}

		//-----------------------------------------------------------------------------
		// Desc: Restores the lost buffer. *pbWasRestored returns TRUE if the buffer was
		//       restored.  It can also NULL if the information is not needed.
		//-----------------------------------------------------------------------------
		HRESULT Sound::RestoreBuffer(LPDIRECTSOUNDBUFFER pDSB, BOOL* pbWasRestored)
		{
			HRESULT hr;

			if (pDSB == NULL)
				return CO_E_NOTINITIALIZED;
			if (pbWasRestored)
				*pbWasRestored = FALSE;

			DWORD dwStatus;
			V(pDSB->GetStatus(&dwStatus));
			if (FAILED(hr))
				return hr;

			if (dwStatus & DSBSTATUS_BUFFERLOST) {
				// Since the app could have just been activated, then
				// DirectSound may not be giving us control yet, so
				// the restoring the buffer may fail.
				// If it does, sleep until DirectSound gives us control.
				do {
					hr = pDSB->Restore();
					if (hr == DSERR_BUFFERLOST)
						Sleep(10);
				} while ((hr = pDSB->Restore()) == DSERR_BUFFERLOST);

				if (pbWasRestored != NULL)
					*pbWasRestored = TRUE;

				return S_OK;
			} else {
				return S_FALSE;
			}
		}

		//-----------------------------------------
		// Desc: Finding the first buffer that is not playing and return a pointer to
		//       it, or if all are playing return a pointer to a randomly selected buffer.
		//-----------------------------------------------------------------------------
		LPDIRECTSOUNDBUFFER Sound::GetFreeBuffer()
		{
			DWORD i;
			if (m_apDSBuffer == NULL)
				return FALSE;

			for (i = 0; i < m_dwNumBuffers; i++) {
				if (m_apDSBuffer[i]) {
					DWORD dwStatus = 0;
					m_apDSBuffer[i]->GetStatus(&dwStatus);
					if ((dwStatus & DSBSTATUS_PLAYING) == 0)
						break;
				}
			}

			if (i != m_dwNumBuffers)
				return m_apDSBuffer[i];
			else
				return m_apDSBuffer[rand() % m_dwNumBuffers];
		}

		//-----------------------------------------------------------------------------
		// Desc:
		//-----------------------------------------------------------------------------
		LPDIRECTSOUNDBUFFER Sound::GetBuffer(DWORD dwIndex)
		{
			if (m_apDSBuffer == NULL)
				return NULL;
			if (dwIndex >= m_dwNumBuffers)
				return NULL;

			return m_apDSBuffer[dwIndex];
		}

		//-----------------------------------------------------------------------------
		// Name: Sound::Get3DBufferInterface()
		// Desc:
		//-----------------------------------------------------------------------------
		HRESULT Sound::Get3DBufferInterface(DWORD dwIndex, LPDIRECTSOUND3DBUFFER* ppDS3DBuffer)
		{
			if (m_apDSBuffer == NULL)
				return CO_E_NOTINITIALIZED;
			if (dwIndex >= m_dwNumBuffers)
				return E_INVALIDARG;

			*ppDS3DBuffer = NULL;

			return m_apDSBuffer[dwIndex]->QueryInterface(IID_IDirectSound3DBuffer,
				(VOID**)ppDS3DBuffer);
		}

		//-----------------------------------------------------------------------------
		// Name: CSound::Play()
		// Desc: Plays the sound using voice management flags.  Pass in DSBPLAY_LOOPING
		//       in the dwFlags to loop the sound
		//-----------------------------------------------------------------------------
		HRESULT Sound::Play(DWORD dwPriority, DWORD dwFlags, LONG lVolume, LONG lFrequency, LONG lPan)
		{
			HRESULT hr;
			BOOL    bRestored;

			if (m_apDSBuffer == NULL)
				return CO_E_NOTINITIALIZED;

			LPDIRECTSOUNDBUFFER pDSB = GetFreeBuffer();

			if (pDSB == NULL)
				return E_FAIL;

			// Restore the buffer if it was lost
			V(RestoreBuffer(pDSB, &bRestored));
			if (FAILED(hr))
				return hr;

			if (bRestored)
			{
				// The buffer was restored, so we need to fill it with new data
				V(FillBufferWithSound(pDSB, FALSE));
				if (FAILED(hr))
					return hr;
			}

			if (m_dwCreationFlags & DSBCAPS_CTRLVOLUME)
			{
				pDSB->SetVolume(lVolume);
			}

			if (lFrequency != -1 &&
				(m_dwCreationFlags & DSBCAPS_CTRLFREQUENCY))
			{
				pDSB->SetFrequency(lFrequency);
			}

			if (m_dwCreationFlags & DSBCAPS_CTRLPAN)
			{
				pDSB->SetPan(lPan);
			}

			return pDSB->Play(0, dwPriority, dwFlags);
		}

		//-----------------------------------------------------------------------------
		// Name: CSound::Play3D()
		// Desc: Plays the sound using voice management flags.  Pass in DSBPLAY_LOOPING
		//       in the dwFlags to loop the sound
		//-----------------------------------------------------------------------------
		HRESULT Sound::Play3D(LPDS3DBUFFER p3DBuffer, DWORD dwPriority, DWORD dwFlags, LONG lFrequency)
		{
			HRESULT hr;
			BOOL    bRestored;
			DWORD   dwBaseFrequency;

			if (m_apDSBuffer == NULL)
				return CO_E_NOTINITIALIZED;

			LPDIRECTSOUNDBUFFER pDSB = GetFreeBuffer();
			if (pDSB == NULL)
				return E_FAIL;

			// Restore the buffer if it was lost
			V(RestoreBuffer(pDSB, &bRestored));
			if (FAILED(hr))
				return hr;

			if (bRestored)
			{
				// The buffer was restored, so we need to fill it with new data
				V(FillBufferWithSound(pDSB, FALSE));
				if (FAILED(hr))
					return hr;
			}

			if (m_dwCreationFlags & DSBCAPS_CTRLFREQUENCY)
			{
				pDSB->GetFrequency(&dwBaseFrequency);
				pDSB->SetFrequency(dwBaseFrequency + lFrequency);
			}

			// QI for the 3D buffer
			LPDIRECTSOUND3DBUFFER pDS3DBuffer;
			V(pDSB->QueryInterface(IID_IDirectSound3DBuffer, (VOID**)&pDS3DBuffer));
			if (SUCCEEDED(hr))
			{
				hr = pDS3DBuffer->SetAllParameters(p3DBuffer, DS3D_IMMEDIATE);
				if (SUCCEEDED(hr))
					hr = pDSB->Play(0, dwPriority, dwFlags);

				pDS3DBuffer->Release();
			}

			return hr;
		}

		//-----------------------------------------------------------------------------
		// Name: CSound::Stop()
		// Desc: Stops the sound from playing
		//-----------------------------------------------------------------------------
		HRESULT Sound::Stop()
		{
			if (m_apDSBuffer == NULL)
				return CO_E_NOTINITIALIZED;

			HRESULT hr = 0;

			for (DWORD i = 0; i < m_dwNumBuffers; i++)
				hr |= m_apDSBuffer[i]->Stop();

			return hr;
		}

		//-----------------------------------------------------------------------------
		// Name: CSound::Reset()
		// Desc: Reset all of the sound buffers
		//-----------------------------------------------------------------------------
		HRESULT Sound::Reset()
		{
			if (m_apDSBuffer == NULL)
				return CO_E_NOTINITIALIZED;

			HRESULT hr = 0;

			for (DWORD i = 0; i < m_dwNumBuffers; i++)
				hr |= m_apDSBuffer[i]->SetCurrentPosition(0);

			return hr;
		}

		//-----------------------------------------------------------------------------
		// Name: CSound::IsSoundPlaying()
		// Desc: Checks to see if a buffer is playing and returns TRUE if it is.
		//-----------------------------------------------------------------------------
		BOOL Sound::IsSoundPlaying()
		{
			BOOL bIsPlaying = FALSE;

			if (m_apDSBuffer == NULL)
				return FALSE;

			for (DWORD i = 0; i < m_dwNumBuffers; i++)
			{
				if (m_apDSBuffer[i])
				{
					DWORD dwStatus = 0;
					m_apDSBuffer[i]->GetStatus(&dwStatus);
					bIsPlaying |= ((dwStatus & DSBSTATUS_PLAYING) != 0);
				}
			}

			return bIsPlaying;
		}
#pragma endregion class SoundBuffer

		//---------------------------------------------------------------------------------------------------------
		// class StreamingSound
#pragma region class StreamingSound
		//-----------------------------------------------------------------------------
		// Name: CStreamingSound::CStreamingSound()
		// Desc: Setups up a buffer so data can be streamed from the wave file into
		//       a buffer.  This is very useful for large wav files that would take a
		//       while to load.  The buffer is initially filled with data, then
		//       as sound is played the notification events are signaled and more data
		//       is written into the buffer by calling HandleWaveStreamNotification()
		//-----------------------------------------------------------------------------
		StreamingSound::StreamingSound(LPDIRECTSOUNDBUFFER pDSBuffer, DWORD dwDSBufferSize,
			WaveFile* pWaveFile, DWORD dwNotifySize)
			: Sound(&pDSBuffer, dwDSBufferSize, 1, pWaveFile, 0)
		{
			m_dwLastPlayPos = 0;
			m_dwPlayProgress = 0;
			m_dwNotifySize = dwNotifySize;
			m_dwNextWriteOffset = 0;
			m_bFillNextNotificationWithSilence = FALSE;
		}

		//-----------------------------------------------------------------------------
		// Name: CStreamingSound::~CStreamingSound()
		// Desc: Destroys the class
		//-----------------------------------------------------------------------------
		StreamingSound::~StreamingSound()
		{
		}

		//-----------------------------------------------------------------------------
		// Name: CStreamingSound::HandleWaveStreamNotification()
		// Desc: Handle the notification that tells us to put more wav data in the
		//       circular buffer
		//-----------------------------------------------------------------------------
		HRESULT StreamingSound::HandleWaveStreamNotification(BOOL bLoopedPlay)
		{
			HRESULT hr;
			DWORD   dwCurrentPlayPos;
			DWORD   dwPlayDelta;
			DWORD   dwBytesWrittenToBuffer;
			VOID*   pDSLockedBuffer = NULL;
			VOID*   pDSLockedBuffer2 = NULL;
			DWORD   dwDSLockedBufferSize;
			DWORD   dwDSLockedBufferSize2;

			if (m_apDSBuffer == NULL || m_pWaveFile == NULL)
				return CO_E_NOTINITIALIZED;

			// Restore the buffer if it was lost
			BOOL bRestored;
			V(RestoreBuffer(m_apDSBuffer[0], &bRestored));
			if (FAILED(hr))
				return hr;

			if (bRestored)
			{
				// The buffer was restored, so we need to fill it with new data
				V(FillBufferWithSound(m_apDSBuffer[0], FALSE));
				if (FAILED(hr))
					return hr;
				return S_OK;
			}

			// Lock the DirectSound buffer
			V(m_apDSBuffer[0]->Lock(m_dwNextWriteOffset, m_dwNotifySize,
				&pDSLockedBuffer, &dwDSLockedBufferSize,
				&pDSLockedBuffer2, &dwDSLockedBufferSize2, 0L));
			if (FAILED(hr))
				return hr;

			// m_dwDSBufferSize and m_dwNextWriteOffset are both multiples of m_dwNotifySize,
			// it should the second buffer, so it should never be valid
			if (pDSLockedBuffer2 != NULL)
				return E_UNEXPECTED;

			if (!m_bFillNextNotificationWithSilence)
			{
				// Fill the DirectSound buffer with wav data
				V(m_apDSBuffer[0]->Lock(m_dwNextWriteOffset, m_dwNotifySize,
					&pDSLockedBuffer, &dwDSLockedBufferSize,
					&pDSLockedBuffer2, &dwDSLockedBufferSize2, 0L));
				if (FAILED(hr))
					return hr;
			}
			else
			{
				// Fill the DirectSound buffer with silence
				FillMemory(pDSLockedBuffer, dwDSLockedBufferSize,
					(BYTE)(m_pWaveFile->m_pwfx->wBitsPerSample == 8 ? 128 : 0));
				dwBytesWrittenToBuffer = dwDSLockedBufferSize;
			}

			// If the number of bytes written is less than the
			// amount we requested, we have a short file.
			if (dwBytesWrittenToBuffer < dwDSLockedBufferSize)
			{
				if (!bLoopedPlay)
				{
					// Fill in silence for the rest of the buffer.
					FillMemory((BYTE*)pDSLockedBuffer + dwBytesWrittenToBuffer,
						dwDSLockedBufferSize - dwBytesWrittenToBuffer,
						(BYTE)(m_pWaveFile->m_pwfx->wBitsPerSample == 8 ? 128 : 0));

					// Any future notifications should just fill the buffer with silence
					m_bFillNextNotificationWithSilence = TRUE;
				}
				else
				{
					// We are looping, so reset the file and fill the buffer with wav data
					DWORD dwReadSoFar = dwBytesWrittenToBuffer;    // From previous call above.
					while (dwReadSoFar < dwDSLockedBufferSize)
					{
						// This will keep reading in until the buffer is full (for very short files).
						V(m_pWaveFile->ResetFile());
						if (FAILED(hr))
							return hr;

						V(m_pWaveFile->Read((BYTE*)pDSLockedBuffer + dwReadSoFar,
							dwDSLockedBufferSize - dwReadSoFar,
							&dwBytesWrittenToBuffer));
						if (FAILED(hr))
							return hr;

						dwReadSoFar += dwBytesWrittenToBuffer;
					}
				}
			}

			// Unlock the DirectSound buffer
			m_apDSBuffer[0]->Unlock(pDSLockedBuffer, dwDSLockedBufferSize, NULL, 0);

			// Figure out how much data has been played so far.  When we have played
			// past the end of the file, we will either need to start filling the
			// buffer with silence or starting reading from the beginning of the file,
			// depending if the user wants to loop the sound
			V(m_apDSBuffer[0]->GetCurrentPosition(&dwCurrentPlayPos, NULL));
			if (FAILED(hr))
				return hr;

			// Check to see if the position counter looped
			if (dwCurrentPlayPos < m_dwLastPlayPos)
				dwPlayDelta = (m_dwDSBufferSize - m_dwLastPlayPos) + dwCurrentPlayPos;
			else
				dwPlayDelta = dwCurrentPlayPos - m_dwLastPlayPos;

			m_dwPlayProgress += dwPlayDelta;
			m_dwLastPlayPos = dwCurrentPlayPos;

			// If we are now filling the buffer with silence, then we have found the end so
			// check to see if the entire sound has played, if it has then stop the buffer.
			if (m_bFillNextNotificationWithSilence)
			{
				// We don't want to cut off the sound before it's done playing.
				if (m_dwPlayProgress >= m_pWaveFile->GetSize())
				{
					m_apDSBuffer[0]->Stop();
				}
			}

			// Update where the buffer will lock (for next time)
			m_dwNextWriteOffset += dwDSLockedBufferSize;
			m_dwNextWriteOffset %= m_dwDSBufferSize; // Circular buffer

			return S_OK;
		}


		// Resets the sound so it will begin playing at the beginning
		HRESULT StreamingSound::Reset()
		{
			HRESULT hr;

			if (m_apDSBuffer[0] == NULL || m_pWaveFile == NULL)
				return CO_E_NOTINITIALIZED;

			m_dwLastPlayPos = 0;
			m_dwPlayProgress = 0;
			m_dwNextWriteOffset = 0;
			m_bFillNextNotificationWithSilence = FALSE;

			// Restore the buffer if it was lost
			BOOL bRestored;
			V(RestoreBuffer(m_apDSBuffer[0], &bRestored));
			if (FAILED(hr))
				return hr;

			if (bRestored) {
				// The buffer was restored, so we need to fill it with new data
				V(FillBufferWithSound(m_apDSBuffer[0], FALSE));
				if (FAILED(hr))
					return hr;
			}

			m_pWaveFile->ResetFile();

			return m_apDSBuffer[0]->SetCurrentPosition(0L);
		}

#pragma endregion class StreamingSound

		//---------------------------------------------------------------------------------------------------------
		// class WaveFile
#pragma region class WaveFile

		//-----------------------------------------------------------------------------
		// Name: CWaveFile::CWaveFile()
		// Desc: Constructs the class.  Call Open() to open a wave file for reading.
		//       Then call Read() as needed.  Calling the destructor or Close()
		//       will close the file.
		//-----------------------------------------------------------------------------
		WaveFile::WaveFile()
		{
			m_pwfx = NULL;
			m_hmmio = NULL;
			m_pResourceBuffer = NULL;
			m_dwSize = 0;
			m_bIsReadingFromMemory = FALSE;
		}

		//-----------------------------------------------------------------------------
		// Name: CWaveFile::~CWaveFile()
		// Desc: Destructs the class
		//-----------------------------------------------------------------------------
		WaveFile::~WaveFile()
		{
			Close();

			if (!m_bIsReadingFromMemory)
				SafeDeleteArray(m_pwfx);
		}

		//-----------------------------------------------------------------------------
		// Name: WaveFile::Open()
		// Desc: Opens a wave file for reading
		//-----------------------------------------------------------------------------
		HRESULT WaveFile::Open(LPTSTR strFileName, WAVEFORMATEX* pwfx, DWORD dwFlags)
		{
			HRESULT hr;

			m_dwFlags = dwFlags;
			m_bIsReadingFromMemory = FALSE;

			if (m_dwFlags == WAVEFILE_READ)
			{
				if (strFileName == NULL)
					return E_INVALIDARG;
				SafeDeleteArray(m_pwfx);

				m_hmmio = mmioOpen(strFileName, NULL, MMIO_ALLOCBUF | MMIO_READ);

				if (NULL == m_hmmio)
				{
					HRSRC   hResInfo;
					HGLOBAL hResData;
					DWORD   dwSize;
					VOID*   pvRes;

					// Loading it as a file failed, so try it as a resource
					if (NULL == (hResInfo = FindResource(NULL, strFileName, _T("WAVE"))))
					{
						if (NULL == (hResInfo = FindResource(NULL, strFileName, _T("WAV"))))
							return E_FAIL;
					}

					if (NULL == (hResData = LoadResource(NULL, hResInfo)))
						return E_FAIL;

					if (0 == (dwSize = SizeofResource(NULL, hResInfo)))
						return E_FAIL;

					if (NULL == (pvRes = LockResource(hResData)))
						return E_FAIL;

					m_pResourceBuffer = new CHAR[dwSize];
					memcpy(m_pResourceBuffer, pvRes, dwSize);

					MMIOINFO mmioInfo;
					ZeroMemory(&mmioInfo, sizeof(mmioInfo));
					mmioInfo.fccIOProc = FOURCC_MEM;
					mmioInfo.cchBuffer = dwSize;
					mmioInfo.pchBuffer = (CHAR*)m_pResourceBuffer;

					m_hmmio = mmioOpen(NULL, &mmioInfo, MMIO_ALLOCBUF | MMIO_READ);
				}

				V(ReadMMIO());
				if (FAILED(hr)) {
					// ReadMMIO will fail if its an not a wave file
					mmioClose(m_hmmio, 0);
					return hr;
				}

				V(ResetFile());
				if (FAILED(hr))
					return hr;

				// After the reset, the size of the wav file is m_ck.cksize so store it now
				m_dwSize = m_ck.cksize;
			}
			else
			{
				m_hmmio = mmioOpen(strFileName, NULL, MMIO_ALLOCBUF |
					MMIO_READWRITE |
					MMIO_CREATE);
				if (NULL == m_hmmio)
					return E_FAIL;

				if (FAILED(hr = WriteMMIO(pwfx))) {
					mmioClose(m_hmmio, 0);
					return hr;
				}

				if (FAILED(hr = ResetFile()))
					return hr;
			}

			return hr;
		}

		//-----------------------------------------------------------------------------
		// Name: WaveFile::OpenFromMemory()
		// Desc: copy data to CWaveFile member variable from memory
		//-----------------------------------------------------------------------------
		HRESULT WaveFile::OpenFromMemory(BYTE* pbData, ULONG ulDataSize,
			WAVEFORMATEX* pwfx, DWORD dwFlags)
		{
			m_pwfx = pwfx;
			m_ulDataSize = ulDataSize;
			m_pbData = pbData;
			m_pbDataCur = m_pbData;
			m_bIsReadingFromMemory = TRUE;

			if (dwFlags != WAVEFILE_READ)
				return E_NOTIMPL;

			return S_OK;
		}

		//-----------------------------------------------------------------------------
		// Name: WaveFile::ReadMMIO()
		// Desc: Support function for reading from a multimedia I/O stream.
		//       m_hmmio must be valid before calling.  This function uses it to
		//       update m_ckRiff, and m_pwfx.
		//-----------------------------------------------------------------------------
		HRESULT WaveFile::ReadMMIO()
		{
			MMCKINFO        ckIn;           // chunk info. for general use.
			PCMWAVEFORMAT   pcmWaveFormat;  // Temp PCM structure to load in.

			m_pwfx = NULL;

			if ((0 != mmioDescend(m_hmmio, &m_ckRiff, NULL, 0)))
				return E_FAIL;

			// Check to make sure this is a valid wave file
			if ((m_ckRiff.ckid != FOURCC_RIFF) ||
				(m_ckRiff.fccType != mmioFOURCC('W', 'A', 'V', 'E')))
				return E_FAIL;

			// Search the input file for for the 'fmt ' chunk.
			ckIn.ckid = mmioFOURCC('f', 'm', 't', ' ');
			if (0 != mmioDescend(m_hmmio, &ckIn, &m_ckRiff, MMIO_FINDCHUNK))
				return E_FAIL;

			// Expect the 'fmt' chunk to be at least as large as <PCMWAVEFORMAT>;
			// if there are extra parameters at the end, we'll ignore them
			if (ckIn.cksize < (LONG) sizeof(PCMWAVEFORMAT))
				return E_FAIL;

			// Read the 'fmt ' chunk into <pcmWaveFormat>.
			if (mmioRead(m_hmmio, (HPSTR)&pcmWaveFormat,
				sizeof(pcmWaveFormat)) != sizeof(pcmWaveFormat))
				return E_FAIL;

			// Allocate the waveformatex, but if its not pcm format, read the next
			// word, and thats how many extra bytes to allocate.
			if (pcmWaveFormat.wf.wFormatTag == WAVE_FORMAT_PCM)
			{
				m_pwfx = (WAVEFORMATEX*)new CHAR[sizeof(WAVEFORMATEX)];
				if (NULL == m_pwfx)
					return E_FAIL;

				// Copy the bytes from the pcm structure to the waveformatex structure
				memcpy(m_pwfx, &pcmWaveFormat, sizeof(pcmWaveFormat));
				m_pwfx->cbSize = 0;
			}
			else
			{
				// Read in length of extra bytes.
				WORD cbExtraBytes = 0L;
				if (mmioRead(m_hmmio, (CHAR*)&cbExtraBytes, sizeof(WORD)) != sizeof(WORD))
					return E_FAIL;

				m_pwfx = (WAVEFORMATEX*)new CHAR[sizeof(WAVEFORMATEX) + cbExtraBytes];
				if (NULL == m_pwfx)
					return E_FAIL;

				// Copy the bytes from the pcm structure to the waveformatex structure
				memcpy(m_pwfx, &pcmWaveFormat, sizeof(pcmWaveFormat));
				m_pwfx->cbSize = cbExtraBytes;

				// Now, read those extra bytes into the structure, if cbExtraAlloc != 0.
				if (mmioRead(m_hmmio, (CHAR*)(((BYTE*)&(m_pwfx->cbSize)) + sizeof(WORD)),
					cbExtraBytes) != cbExtraBytes)
				{
					SafeDelete(m_pwfx);
					return E_FAIL;
				}
			}

			// Ascend the input file out of the 'fmt ' chunk.
			if (0 != mmioAscend(m_hmmio, &ckIn, 0))
			{
				SafeDelete(m_pwfx);
				return E_FAIL;
			}

			return S_OK;
		}

		//-----------------------------------------------------------------------------
		// Name: WaveFile::GetSize()
		// Desc: Retuns the size of the read access wave file
		//-----------------------------------------------------------------------------
		DWORD WaveFile::GetSize()
		{
			return m_dwSize;
		}

		//-----------------------------------------------------------------------------
		// Name: WaveFile::ResetFile()
		// Desc: Resets the internal m_ck pointer so reading starts from the
		//       beginning of the file again
		//-----------------------------------------------------------------------------
		HRESULT WaveFile::ResetFile()
		{
			if (m_bIsReadingFromMemory)
			{
				m_pbDataCur = m_pbData;
			}
			else
			{
				if (m_hmmio == NULL)
					return CO_E_NOTINITIALIZED;

				if (m_dwFlags == WAVEFILE_READ)
				{
					// Seek to the data
					if (-1 == mmioSeek(m_hmmio, m_ckRiff.dwDataOffset + sizeof(FOURCC),
						SEEK_SET))
						return E_FAIL;

					// Search the input file for the 'data' chunk.
					m_ck.ckid = mmioFOURCC('d', 'a', 't', 'a');
					if (0 != mmioDescend(m_hmmio, &m_ck, &m_ckRiff, MMIO_FINDCHUNK))
						return E_FAIL;
				}
				else
				{
					// Create the 'data' chunk that holds the waveform samples.
					m_ck.ckid = mmioFOURCC('d', 'a', 't', 'a');
					m_ck.cksize = 0;

					if (0 != mmioCreateChunk(m_hmmio, &m_ck, 0))
						return E_FAIL;

					if (0 != mmioGetInfo(m_hmmio, &m_mmioinfoOut, 0))
						return E_FAIL;
				}
			}

			return S_OK;
		}

		//-----------------------------------------------------------------------------
		// Name: CWaveFile::Read()
		// Desc: Reads section of data from a wave file into pBuffer and returns
		//       how much read in pdwSizeRead, reading not more than dwSizeToRead.
		//       This uses m_ck to determine where to start reading from.  So
		//       subsequent calls will be continue where the last left off unless
		//       Reset() is called.
		//-----------------------------------------------------------------------------
		HRESULT WaveFile::Read(BYTE* pBuffer, DWORD dwSizeToRead, DWORD* pdwSizeRead)
		{
			if (m_bIsReadingFromMemory)
			{
				if (m_pbDataCur == NULL)
					return CO_E_NOTINITIALIZED;
				if (pdwSizeRead != NULL)
					*pdwSizeRead = 0;

				if ((BYTE*)(m_pbDataCur + dwSizeToRead) >
					(BYTE*)(m_pbData + m_ulDataSize))
				{
					dwSizeToRead = m_ulDataSize - (DWORD)(m_pbDataCur - m_pbData);
				}

				CopyMemory(pBuffer, m_pbDataCur, dwSizeToRead);

				if (pdwSizeRead != NULL)
					*pdwSizeRead = dwSizeToRead;

				return S_OK;
			}
			else
			{
				MMIOINFO mmioinfoIn; // current status of m_hmmio

				if (m_hmmio == NULL)
					return CO_E_NOTINITIALIZED;
				if (pBuffer == NULL || pdwSizeRead == NULL)
					return E_INVALIDARG;

				if (pdwSizeRead != NULL)
					*pdwSizeRead = 0;

				if (0 != mmioGetInfo(m_hmmio, &mmioinfoIn, 0))
					return E_FAIL;

				UINT cbDataIn = dwSizeToRead;
				if (cbDataIn > m_ck.cksize)
					cbDataIn = m_ck.cksize;

				m_ck.cksize -= cbDataIn;

				for (DWORD cT = 0; cT < cbDataIn; cT++)
				{
					// Copy the bytes from the io to the buffer.
					if (mmioinfoIn.pchNext == mmioinfoIn.pchEndRead)
					{
						if (0 != mmioAdvance(m_hmmio, &mmioinfoIn, MMIO_READ))
							return E_FAIL;

						if (mmioinfoIn.pchNext == mmioinfoIn.pchEndRead)
							return E_FAIL;
					}

					// Actual copy.
					*((BYTE*)pBuffer + cT) = *((BYTE*)mmioinfoIn.pchNext);
					mmioinfoIn.pchNext++;
				}

				if (0 != mmioSetInfo(m_hmmio, &mmioinfoIn, 0))
					return E_FAIL;

				if (pdwSizeRead != NULL)
					*pdwSizeRead = cbDataIn;

				return S_OK;
			}
		}

		//-----------------------------------------------------------------------------
		// Name: WaveFile::Close()
		// Desc: Closes the wave file
		//-----------------------------------------------------------------------------
		HRESULT WaveFile::Close()
		{
			if (m_dwFlags == WAVEFILE_READ)
			{
				mmioClose(m_hmmio, 0);
				m_hmmio = NULL;
				SafeDeleteArray(m_pResourceBuffer);
			}
			else
			{
				m_mmioinfoOut.dwFlags |= MMIO_DIRTY;

				if (m_hmmio == NULL)
					return CO_E_NOTINITIALIZED;

				if (0 != mmioSetInfo(m_hmmio, &m_mmioinfoOut, 0))
					return E_FAIL;

				// Ascend the output file out of the 'data' chunk -- this will cause
				// the chunk size of the 'data' chunk to be written.
				if (0 != mmioAscend(m_hmmio, &m_ck, 0))
					return E_FAIL;

				// Do this here instead...
				if (0 != mmioAscend(m_hmmio, &m_ckRiff, 0))
					return E_FAIL;

				mmioSeek(m_hmmio, 0, SEEK_SET);

				if (0 != (INT)mmioDescend(m_hmmio, &m_ckRiff, NULL, 0))
					return E_FAIL;

				m_ck.ckid = mmioFOURCC('f', 'a', 'c', 't');

				if (0 == mmioDescend(m_hmmio, &m_ck, &m_ckRiff, MMIO_FINDCHUNK))
				{
					DWORD dwSamples = 0;
					mmioWrite(m_hmmio, (HPSTR)&dwSamples, sizeof(DWORD));
					mmioAscend(m_hmmio, &m_ck, 0);
				}

				// Ascend the output file out of the 'RIFF' chunk -- this will cause
				// the chunk size of the 'RIFF' chunk to be written.
				if (0 != mmioAscend(m_hmmio, &m_ckRiff, 0))
					return E_FAIL;

				mmioClose(m_hmmio, 0);
				m_hmmio = NULL;
			}

			return S_OK;
		}

		//-----------------------------------------------------------------------------
		// Name: WaveFile::WriteMMIO()
		// Desc: Support function for reading from a multimedia I/O stream
		//       pwfxDest is the WAVEFORMATEX for this new wave file.
		//       m_hmmio must be valid before calling.  This function uses it to
		//       update m_ckRiff, and m_ck.
		//-----------------------------------------------------------------------------
		HRESULT WaveFile::WriteMMIO(WAVEFORMATEX *pwfxDest)
		{
			DWORD    dwFactChunk; // Contains the actual fact chunk. Garbage until WaveCloseWriteFile.
			MMCKINFO ckOut1;

			dwFactChunk = (DWORD)-1;

			// Create the output file RIFF chunk of form type 'WAVE'.
			m_ckRiff.fccType = mmioFOURCC('W', 'A', 'V', 'E');
			m_ckRiff.cksize = 0;

			if (0 != mmioCreateChunk(m_hmmio, &m_ckRiff, MMIO_CREATERIFF))
				return  E_FAIL;

			// We are now descended into the 'RIFF' chunk we just created.
			// Now create the 'fmt ' chunk. Since we know the size of this chunk,
			// specify it in the MMCKINFO structure so MMIO doesn't have to seek
			// back and set the chunk size after ascending from the chunk.
			m_ck.ckid = mmioFOURCC('f', 'm', 't', ' ');
			m_ck.cksize = sizeof(PCMWAVEFORMAT);

			if (0 != mmioCreateChunk(m_hmmio, &m_ck, 0))
				return  E_FAIL;

			// Write the PCMWAVEFORMAT structure to the 'fmt ' chunk if its that type.
			if (pwfxDest->wFormatTag == WAVE_FORMAT_PCM)
			{
				if (mmioWrite(m_hmmio, (HPSTR)pwfxDest,
					sizeof(PCMWAVEFORMAT)) != sizeof(PCMWAVEFORMAT))
					return  E_FAIL;
			}
			else
			{
				// Write the variable length size.
				if ((UINT)mmioWrite(m_hmmio, (HPSTR)pwfxDest,
					sizeof(*pwfxDest) + pwfxDest->cbSize) !=
					(sizeof(*pwfxDest) + pwfxDest->cbSize))
					return E_FAIL;
			}

			// Ascend out of the 'fmt ' chunk, back into the 'RIFF' chunk.
			if (0 != mmioAscend(m_hmmio, &m_ck, 0))
				return  E_FAIL;

			// Now create the fact chunk, not required for PCM but nice to have.  This is filled
			// in when the close routine is called.
			ckOut1.ckid = mmioFOURCC('f', 'a', 'c', 't');
			ckOut1.cksize = 0;

			if (0 != mmioCreateChunk(m_hmmio, &ckOut1, 0))
				return  E_FAIL;

			if (mmioWrite(m_hmmio, (HPSTR)&dwFactChunk, sizeof(dwFactChunk)) !=
				sizeof(dwFactChunk))
				return  E_FAIL;

			// Now ascend out of the fact chunk...
			if (0 != mmioAscend(m_hmmio, &ckOut1, 0))
				return E_FAIL;

			return S_OK;
		}

		//-----------------------------------------------------------------------------
		// Name: WaveFile::Write()
		// Desc: Writes data to the open wave file
		//-----------------------------------------------------------------------------
		HRESULT WaveFile::Write(UINT nSizeToWrite, BYTE* pbSrcData, UINT* pnSizeWrote)
		{
			UINT cT;

			if (m_bIsReadingFromMemory)
				return E_NOTIMPL;
			if (m_hmmio == NULL)
				return CO_E_NOTINITIALIZED;
			if (pnSizeWrote == NULL || pbSrcData == NULL)
				return E_INVALIDARG;

			*pnSizeWrote = 0;

			for (cT = 0; cT < nSizeToWrite; cT++)
			{
				if (m_mmioinfoOut.pchNext == m_mmioinfoOut.pchEndWrite)
				{
					m_mmioinfoOut.dwFlags |= MMIO_DIRTY;
					if (0 != mmioAdvance(m_hmmio, &m_mmioinfoOut, MMIO_WRITE))
						return  E_FAIL;
				}

				*((BYTE*)m_mmioinfoOut.pchNext) = *((BYTE*)pbSrcData + cT);
				(BYTE*)m_mmioinfoOut.pchNext++;

				(*pnSizeWrote)++;
			}

			return S_OK;
		}

#pragma endregion class WaveFile
	} /* namespace Audio */
} /* namespace System */

#endif