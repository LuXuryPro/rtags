/* This file is part of RTags (http://rtags.net).

   RTags is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   RTags is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with RTags.  If not, see <http://www.gnu.org/licenses/>. */

#ifndef RClient_h
#define RClient_h

#include "QueryMessage.h"
#include "rct/List.h"
#include "rct/Message.h"
#include "rct/Path.h"
#include "rct/Set.h"
#include "rct/String.h"

class RCCommand;
class QueryCommand;
class Connection;
class RClient
{
public:
    enum OptionType {
        None = 0,
        AbsolutePath,
        AllReferences,
        AllDependencies,
        AllTargets,
        Autotest,
        BuildIndex,
        CheckIncludes,
        CheckReindex,
        ClassHierarchy,
        Clear,
        CodeCompleteAt,
        CodeCompleteIncludeMacros,
        CompilationFlagsOnly,
        CompilationFlagsSplitLine,
        Compile,
        ConnectTimeout,
        ContainingFunction,
        ContainingFunctionLocation,
        CurrentFile,
        CurrentProject,
        CursorKind,
        DebugLocations,
        DeclarationOnly,
        DefinitionOnly,
        DeleteProject,
        Dependencies,
        DependencyFilter,
        Diagnose,
        Diagnostics,
        DisplayName,
        DumpCompilationDatabase,
        DumpCompletions,
        DumpFile,
        DumpFileMaps,
        DumpIncludeHeaders,
        Elisp,
        FilterSystemHeaders,
        FindFile,
        FindFilePreferExact,
        FindProjectBuildRoot,
        FindProjectRoot,
        FindSymbols,
        FindVirtuals,
        FixIts,
        FollowLocation,
        GenerateTest,
        GuessFlags,
        HasFileManager,
        Help,
        IncludeFile,
        IMenu,
        IsIndexed,
        IsIndexing,
        JobCount,
        KindFilter,
        ListBuffers,
        ListSymbols,
        LoadCompilationDatabase,
        LogFile,
        Man,
        MatchCaseInsensitive,
        MatchRegex,
        Max,
        NoColor,
        NoContext,
        NoSortReferencesByInput,
        PathFilter,
        PrepareCodeCompleteAt,
        PreprocessFile,
        Project,
        ProjectRoot,
        QuitRdm,
        RTagsConfig,
        RangeFilter,
        RdmLog,
        ReferenceLocation,
        ReferenceName,
        Reindex,
        ReloadFileManager,
        RemoveFile,
        Rename,
        ReverseSort,
        SendDiagnostics,
        SetBuffers,
        Silent,
        SilentQuery,
        SocketAddress,
        SocketFile,
        Sources,
        Status,
        StripParen,
        Suspend,
        SymbolInfo,
        SymbolInfoIncludeParents,
        SymbolInfoExcludeReferences,
        SymbolInfoExcludeTargets,
        SynchronousCompletions,
        Timeout,
        UnsavedFile,
        Verbose,
        Version,
        Wait,
        WildcardSymbolNames,
        NumOptions
    };

    enum Flag {
        Flag_None = 0x0,
        Flag_Autotest = 0x1
    };

    RClient();
    ~RClient();
    int exec();
    enum ParseStatus {
        Parse_Exec,
        Parse_Ok,
        Parse_Error
    };
    ParseStatus parse(int &argc, char **argv);

    Flags<Flag> flags() const { return mFlags; }

    int max() const { return mMax; }
    LogLevel logLevel() const { return mLogLevel; }
    int timeout() const { return mTimeout; }
    int buildIndex() const { return mBuildIndex; }

    const Set<QueryMessage::PathFilter> &pathFilters() const { return mPathFilters; }
    int minOffset() const { return mMinOffset; }
    int maxOffset() const { return mMaxOffset; }

    const Set<String> &kindFilters() const { return mKindFilters; }

    const UnsavedFiles &unsavedFiles() const { return mUnsavedFiles; }

    const List<String> &rdmArgs() const { return mRdmArgs; }
    const Path &currentFile() const { return mCurrentFile; }

    String socketFile() const { return mSocketFile; }
    String tcpHost() const { return mTcpHost; }
    uint16_t tcpPort() const { return mTcpPort; }
    Path projectRoot() const { return mProjectRoot; }
    Flags<QueryMessage::Flag> queryFlags() const { return mQueryFlags; }
    int terminalWidth() const { return mTerminalWidth; }

    int argc() const { return mArgc; }
    char **argv() const { return mArgv; }
    void onNewMessage(const std::shared_ptr<Message> &message, const std::shared_ptr<Connection> &);
    List<Path> pathEnvironment() const;
private:
    void addQuery(QueryMessage::Type t, const String &query = String(),
                  Flags<QueryMessage::Flag> extraQueryFlags = Flags<QueryMessage::Flag>());
    void addQuitCommand(int exitCode);

    void addLog(LogLevel level);
    void addCompile(const Path &cwd, const String &args);
    void addCompile(const Path &dir);

    Flags<Flag> mFlags;
    Flags<QueryMessage::Flag> mQueryFlags;
    int mMax, mTimeout, mMinOffset, mMaxOffset, mConnectTimeout, mBuildIndex;
    LogLevel mLogLevel;
    Set<QueryMessage::PathFilter> mPathFilters;
    Set<String> mKindFilters;
    UnsavedFiles mUnsavedFiles;
    List<std::shared_ptr<RCCommand> > mCommands;
    List<String> mRdmArgs;
    Path mSocketFile;
    Path mCurrentFile;
    String mTcpHost;
    uint16_t mTcpPort;
    bool mGuessFlags;
    Path mProjectRoot;
    int mTerminalWidth;
    mutable List<Path> mPathEnvironment;

    int mArgc;
    char **mArgv;

    friend class CompileCommand;
};

RCT_FLAGS(RClient::Flag);

#endif
