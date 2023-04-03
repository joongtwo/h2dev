@echo off

SET TC_ROOT=C:\Siemens\Teamcenter13
SET TC_DATA=C:\Siemens\tcdata
call %TC_DATA%\tc_profilevars

cd /d %TC_ROOT%\bmide\workspace\13000.0.0\h2dev\Environment\Workflow

echo ######################################################################
echo #                  Import Workflow Process Template                  #
echo ######################################################################

echo # Import My Workflow Template Start...
plmxml_import -u=infodba -p=infodba -g=dba -ignore_originid -transfermode=workflow_template_overwrite -xml_file="My Workflow Template.xml"
echo ## Import My Workflow Template Success...


echo ######################################################################
echo #           Import Workflow Process Template Complete                #
echo ######################################################################

timeout /t 5

@echo on