      FUNCTION F_MAIN()

      IMPLICIT NONE
      INCLUDE 'IPhreeqc.f.inc'
      INTEGER(KIND=4) id

      INTEGER(KIND=4)    r
      INTEGER(KIND=4)    c
      INTEGER(KIND=4)    t
      REAL(KIND=8)       d
      CHARACTER(LEN=80)  s

      INTEGER(KIND=4) F_MAIN
      INTEGER(KIND=4) TestGetSet

      INTEGER(KIND=4) EXIT_SUCCESS
      PARAMETER (EXIT_SUCCESS=0)

      INTEGER(KIND=4) EXIT_FAILURE
      PARAMETER (EXIT_FAILURE=1)

      EXTERNAL GetDumpFileOn
      EXTERNAL SetDumpFileOn

      EXTERNAL GetDumpStringOn
      EXTERNAL SetDumpStringOn

      EXTERNAL GetErrorFileOn
      EXTERNAL SetErrorFileOn

      EXTERNAL GetLogFileOn
      EXTERNAL SetLogFileOn

      EXTERNAL GetOutputFileOn
      EXTERNAL SetOutputFileOn

      EXTERNAL GetSelectedOutputFileOn
      EXTERNAL SetSelectedOutputFileOn

      id = CreateIPhreeqc()
      IF (id.LT.0) THEN
         F_MAIN = EXIT_FAILURE
         RETURN
      ENDIF

C     Dump
      IF (TestGetSet(id,GetDumpFileOn,SetDumpFileOn).NE.0) THEN
         F_MAIN = EXIT_FAILURE
         RETURN
      ENDIF
      
C     Dump string
      IF (TestGetSet(id,GetDumpStringOn,SetDumpStringOn).NE.0) THEN
         F_MAIN = EXIT_FAILURE
         RETURN
      ENDIF
      
C     Error
      IF (TestGetSet(id,GetErrorFileOn,SetErrorFileOn).NE.0) THEN
         F_MAIN = EXIT_FAILURE
         RETURN
      ENDIF
      
C     Log
      IF (TestGetSet(id,GetLogFileOn,SetLogFileOn).NE.0) THEN
         F_MAIN = EXIT_FAILURE
         RETURN
      ENDIF
      
C     Output
      IF (TestGetSet(id,GetOutputFileOn,SetOutputFileOn).NE.0) THEN
         F_MAIN = EXIT_FAILURE
         RETURN
      ENDIF
      
C     Selected output
      IF (TestGetSet(id,GetSelectedOutputFileOn,SetSelectedOutputFileOn)
     &     .NE.0) THEN
         F_MAIN = EXIT_FAILURE
         RETURN
      ENDIF
      
      IF (LoadDatabase(id, "phreeqc.dat").NE.0) THEN
         CALL OutputErrorString(id)
         F_MAIN = EXIT_FAILURE
         RETURN
      ENDIF
      
      IF (RunFile(id, "ex2").NE.0) THEN
         CALL OutputErrorString(id)
         F_MAIN = EXIT_FAILURE
         RETURN
      ENDIF
      
      DO 20 r=0,GetSelectedOutputRowCount(id)
         DO 10 c=1,GetSelectedOutputColumnCount(id)
            IF (GetSelectedOutputValue(id,r,c,t,d,s).NE.IPQ_OK) THEN
               CALL OutputErrorString(id)
               F_MAIN = EXIT_FAILURE
               RETURN
            ENDIF
 10      CONTINUE
 20   CONTINUE
      
      IF (DestroyIPhreeqc(id).NE.0) THEN
         CALL OutputErrorString(id)
         F_MAIN = EXIT_FAILURE
         RETURN
      ENDIF
      
      F_MAIN = EXIT_SUCCESS
      RETURN
      
      END FUNCTION F_MAIN
      
      




      FUNCTION TestGetSet(id,getFunc,setFunc)
      
      IMPLICIT NONE
      INCLUDE 'IPhreeqc.f.inc'
      INTEGER(KIND=4) id
      INTEGER(KIND=4) TestGetSet
      
      LOGICAL(KIND=4) getFunc
      INTEGER(KIND=4) setFunc
      
      INTEGER(KIND=4) EXIT_SUCCESS
      PARAMETER (EXIT_SUCCESS=0)
      
      INTEGER(KIND=4) EXIT_FAILURE
      PARAMETER (EXIT_FAILURE=1)
      
      IF (getFunc(id)) THEN
         TestGetSet = EXIT_FAILURE
         RETURN
      ENDIF
      
      IF (setFunc(id,.TRUE.).NE.IPQ_OK) THEN
         TestGetSet = EXIT_FAILURE
         RETURN
      ENDIF
      
      IF (.NOT.getFunc(id)) THEN
         TestGetSet = EXIT_FAILURE
         RETURN
      ENDIF
      
      IF (setFunc(id,.FALSE.).NE.IPQ_OK) THEN
         TestGetSet = EXIT_FAILURE
         RETURN
      ENDIF
      
      TestGetSet = EXIT_SUCCESS
      RETURN
      
      END FUNCTION TestGetSet
