#include "battleinterface.h"
#include "battlepluginstruct.h"
#include "plugininterface.h"

BattlePStorage::BattlePStorage(BattlePlugin *p)
{
    for (int i = 0; i < lastEnum; i++) {
        calls[i] = NULL;
    }

    QHash<QString, Hook> functions = p->getHooks();

    if (functions.contains("battleStarting(BattleInterface&)")) {
        calls[battleStarting] = functions.value("battleStarting(BattleInterface&)");

        functions.remove("battleStarting(BattleInterface&)");
    }

    if (functions.contains("emitCommand(BattleInterface&,int,QByteArray&")) {
        calls[emitCommand] = functions.value("emitCommand(BattleInterface&,int,QByteArray&");

        functions.remove("emitCommand(BattleInterface&,int,int,QByteArray");
    }

    if (!functions.empty()) {
        /* To Do: Some way to propagate an error about unreckognized stuff, maybe cancel the plugin entirely */
    }

    plugin = p;
}

BattlePStorage::~BattlePStorage()
{
    delete plugin;
}

int BattlePStorage::call(int f, BattleInterface *b)
{
    if (calls[f]) {
        /* Calls the plugin member function, from the correct class, with the appropriate parameters */
        return (*plugin.*(reinterpret_cast<int (BattlePlugin::*)(BattleInterface &)>(calls[f])))(*b);
    }

    return 0;
}
