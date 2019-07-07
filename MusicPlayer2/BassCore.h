#pragma once
#include "IPlayerCore.h"
#include "bass.h"
#include "BASSMidiLibrary.h"

class CBassCore :
    public IPlayerCore
{
public:
    CBassCore();
    ~CBassCore();

    virtual void InitCore() override;
    virtual void UnInitCore() override;
    virtual unsigned int GetHandle() override;

    virtual std::wstring GetAudioType() override;
    virtual int GetChannels() override;
    virtual int GetFReq() override;
    virtual const wstring& GetSoundFontName() override;

    virtual void Open(const wchar_t* file_path) override;
    virtual void Close() override;
    virtual void Play() override;
    virtual void Pause() override;
    virtual void Stop() override;
    virtual void SetVolume(int volume) override;

    virtual int GetCurPosition() override;
    virtual int GetSongLength() override;
    virtual void SetCurPosition(int position) override;

    virtual bool IsMidi() override;
    virtual bool IsMidiConnotPlay() override;
    virtual std::wstring GetMidiInnerLyric() override;
    virtual MidiInfo GetMidiInfo() override;
    virtual bool MidiNoLyric() override;

    struct MidiLyricInfo 
    {
        wstring midi_lyric;
        bool midi_no_lyric;
    };

public:
    static CBASSMidiLibrary m_bass_midi_lib;
    static BASS_MIDI_FONT m_sfont;	//MIDI��ɫ��

private:
    //��ȡMidi������Ƕ��ʵĻص�����
    static void CALLBACK MidiLyricSync(HSYNC handle, DWORD channel, DWORD data, void *user);
    static void CALLBACK MidiEndSync(HSYNC handle, DWORD channel, DWORD data, void *user);

    void GetMidiPosition();

private:
    HSTREAM m_musicStream{};		//��ǰ����Ƶ���
    vector<HPLUGIN> m_plugin_handles;		//����ľ��
    wstring m_sfont_name;		//MIDI��ɫ�������
    static MidiLyricInfo m_midi_lyric;
    BASS_CHANNELINFO m_channel_info;	//��Ƶͨ������Ϣ
    bool m_is_midi;
    MidiInfo m_midi_info;

};
