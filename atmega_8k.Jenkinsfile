pipeline {
  agent any

  //environment {
  //  BUILD_EMAIL_TO = ""
  //  BUILD_EMAIL_BODY = """build info: ${env.BUILD_URL}"""
  //}

  parameters {
    choice(name: "AVR_FR_OPT", choices: ["old", "new"], description: "FreeRTOS AVR port")
  }

  options {
    buildDiscarder(logRotator(artifactDaysToKeepStr: "", artifactNumToKeepStr: "", daysToKeepStr: "", numToKeepStr: "8"))
  }

  triggers {
    pollSCM ("H/30 * * * *")
  }

  def MCUS = ["atmega8", "atmega8a", "atmega8hva", "atmega8u2", "atmega8515", "atmega8535"]
  stages {
    stage ("env") {
      steps {
        sh "env"
      }
    }
    stage ("extra SCM") {
      steps {
        checkout([$class: 'GitSCM', branches: [[name: '*/master']], doGenerateSubmoduleConfigurations: false,
                  extensions: [[$class: 'RelativeTargetDirectory', relativeTargetDir: 'FreeRTOS-Kernel'], [$class: 'CleanCheckout']],
                  submoduleCfg: [],
                  userRemoteConfigs: [[url: 'https://github.com/jonsnow1357/FreeRTOS-Kernel.git']]
        ])
      }
    }
    for (int i = 0; i < MCUS.length; i++) {
      stage ("${MCUS[i]}") {
        steps {
          catchError(buildResult: "FAILURE", stageResult: "FAILURE") {
            sh "mkdir -p build; cd build; rm -rvf *; cmake -DAVR_MCU=${MCUS[i]} -DAVR_FR_OPT=${params.AVR_FR_OPT} ..; make;"
          }
        }
      }
    }
  }

  post {
    //always {
    //  junit allowEmptyResults: true, testResults: "${PY_MODULE}/tests/data_out/test_py*.xml"
    //}
    //failure {
    //  emailext (
    //    subject: "FAILURE: Job '${env.JOB_NAME} [${env.BUILD_NUMBER}]'",
    //    body: "${BUILD_EMAIL_BODY}",
    //    to: "${BUILD_EMAIL_TO}"
    //  )
    //}
    //aborted {
    //  emailext (
    //    subject: "ABORTED: Job '${env.JOB_NAME} [${env.BUILD_NUMBER}]'",
    //    body: "${BUILD_EMAIL_BODY}",
    //    to: "${BUILD_EMAIL_TO}"
    //  )
    //}
    //unstable {
    //  emailext (
    //    subject: "UNSTABLE: Job '${env.JOB_NAME} [${env.BUILD_NUMBER}]'",
    //    body: "${BUILD_EMAIL_BODY}",
    //    to: "${BUILD_EMAIL_TO}"
    //  )
    //}
    cleanup{
      deleteDir()
    }
  }
}
