![SnowPME Logo](https://raw.githubusercontent.com/KuromeSan/SnowPME/master/Logo.png)

An experimental PlayStation Mobile Emulator for Windows !

NOTE: This is VERY EARLY in development, so nothing runs at all yet except some *really* basic SDK Samples .. 



-- About usage of the term "Emulator" --
i can already hear all the angry nerds telling me you cant make a PSM emulator because PSM im not emulating any CPU!
its a Runtime Environment, and is built upon Mono Framework! Thats like calling .NET framework or Java an emulator!11

Okay, i give you this *What exactly is the difference between a Runtime like .NET or the JVM,* and a console emulator (say like mGBA?)
like JVM essentially just emulates a processor that doesnt exist- 
common answer i hear is something about  say something like isolation, like software running in mono/java/etc still have access to the whole system,
but a GBA emulator does not.
however, this is also true for PSM- only access to /Documents, /Application, and /Temp folders respectively
as well as having memory limitations, on how many threads can be used, as well as no access to Marshal or any ability to call native DLLs/code

heck ok, if Ruffle can call themselves an emulator, for essentially being the same thing, so can i-
its app that runs software, designed for something else, alright?
Sooo Emulator that's what im going with, deal with it.
