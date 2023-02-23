class SessionManager
{

    bool spinOnce(double fCurrentTime, std::vector<::vts::protocol::main::PubRole> &vecProtoPubRole, std::map<std::string, std::vector<std::string> > &mapRoleNeedRemoved);

    bool addPubRole(const std::string strSessionId, const ::vts::protocol::main::PubRole &protoPubRole);    //add SingleRole by sessionID
    bool getPubRole(const std::string strSessionId, std::unordered_map<std::string, ::vts::protocol::main::SingleRole> &mapSingleRole);

private:
    SessionManager();

private:
    std::string mstrTestcaseFilePath;
    std::string mstrClientID;
    std::mutex mmuxPlate;
    std::unordered_map<std::string,eSessionState> mmapSessionState;//(session id, session state)

    std::mutex mMutex;
    static Ptr mpVehicleManager;
    std::unordered_map<std::string, Testcase::Ptr> mmapTestcase;// (testcase name, testcase file)
    std::unordered_map<std::string, std::vector<VehicleLauncher::Ptr> > mmapSession2Launcher;//(session id, vehicle launchers)
    std::unordered_map<std::string, Testcase::Ptr> mmapSession2Testcase;//(session id, vehicle launchers)
    std::unordered_map<std::string, double> mmapSession2LocalTime;//(session id, the session run time)

    std::unordered_map<std::string, std::set<std::string> > mmapSession2Plates;//(session id, vehicle launchers)

    std::mutex mMutexSingleRole;
    //(session id, <vehicle id, SingleRole>),come from serve
    std::unordered_map<std::string, std::unordered_map<std::string, ::vts::protocol::main::SingleRole> > mmapProtoSingleRole;
    //(session id, <vehicle id, SingleRole>),from self generate
    std::unordered_map<std::string, std::unordered_map<std::string, ::vts::protocol::main::SingleRole> > mmapSelfSingleRole;

    std::unordered_map<std::string, std::string> mmapSessionTesteeID;//(session id, testee id)

};

bool SessionManager::spinOnce(double dDeltaTime, std::vector<::vts::protocol::main::PubRole>& vecProtoPubRole,
                                              std::map<std::string, std::vector<std::string> > &mapRoleNeedRemoved)
{
    static ::google::protobuf::RepeatedPtrField<::vts::protocol::main::SingleRole> protoSingleRoles;
    static size_t nBufSize=0;
    std::unique_lock<std::mutex> lock(mMutex);

    for (auto&it:mmapSession2Launcher)
    {
        std::string strSessionId = it.first;
        auto state = mmapSessionState.find(strSessionId);
        std::unordered_map<std::string, ::vts::protocol::main::SingleRole> umapSingleRole;
        //获取
        getPubRole(strSessionId, umapSingleRole);  //get all SingleRole from server
        //

    }

bool SessionManager::addPubRole(const std::string strSessionId, const vts::protocol::main::PubRole &protoPubRole)
{
    std::unique_lock<std::mutex> lock(mMutexSingleRole);
    auto state = mmapSessionState.find(strSessionId);
    if(state == mmapSessionState.end())
    {
        return false;
    }
    if(state->second == eSessionState::SESSION_CONTINUOUS_RUNNING or state->second == eSessionState::SESSION_STEP_RUNNING)
    {
        //if sessionID is exit,update singleRole
        auto mapSingleRoleIdx = mmapProtoSingleRole.find(strSessionId);     //<roleID,singleRole>
        if(mapSingleRoleIdx != mmapProtoSingleRole.end())
        {
            //traversal all SingleRole,put into the buffer of mmapProtoSingleRole
            mapSingleRoleIdx->second.clear();   //first clear all old pubRole from serve.
            for(auto &asingleRole : vecSingleRole)
            {
                mapSingleRoleIdx->second.insert(std::make_pair(asingleRole.id(),asingleRole));
            }
        }
        else
        {
            std::unordered_map<std::string, ::vts::protocol::main::SingleRole> mapSingleRole;
            for(auto &singleRole : vecSingleRole)
            {
               mapSingleRole.insert(std::make_pair(singleRole.id(), singleRole));
            }
            mmapProtoSingleRole.insert(std::make_pair(strSessionId, mapSingleRole));
        }
        return true;
    }
    else
    {
        return false;
    }
}
bool SessionManager::getPubRole(const std::string strSessionId, std::unordered_map<std::string, vts::protocol::main::SingleRole> &mapSingleRole)
{
    std::unique_lock<std::mutex> lock(mMutexSingleRole);
    auto mapSingRoleIdx = mmapProtoSingleRole.find(strSessionId);
    if(mapSingRoleIdx != mmapProtoSingleRole.end())
    {
        mapSingleRole = mapSingRoleIdx->second;
    }

    return true;
}