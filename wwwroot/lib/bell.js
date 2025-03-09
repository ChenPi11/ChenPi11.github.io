"use strict";const BELL_AUDIO_PATH="/media/bell.mp3";var audio;$((function(){audio=new Audio(BELL_AUDIO_PATH);audio.load()}));export function playBell(){audio.play()}
